
#include <iostream>
#include <cassert>
#include <cstdlib>

#include "il.h"
#include "ilu.h"

#include "log.hpp"
#include "stationParser.hpp"
#include "dataParser.hpp"
#include "simpleShepardInterpolator.hpp"
#include "linearColorizer.hpp"
#include "imageGenerator.hpp"

int main(int argc, char** argv) {

    // Initialize Logs
    using log4cpp::log_console;
    log4cpp::initLogs();
    log_console->infoStream() << "Projet de visualisation !";
    
    // Initialize DevIL
    ilInit();

    // Parse stations
    StationParser sp;
    std::map<std::string, Station*> stations = sp.parse("data/stations.data");

    // Parse sensor data
    DataParser dp;
    dp.parseSensorData("data/particules.data", stations);

    // Change data layout of a given sensor (AoS to SaO)
    const std::string sensorName("Particules PM10");
    SensorDataArray<int> sensorData = buildSensorDataArray(stations, sensorName);

    // Print data of the first hour
    log_console->infoStream() << "First hour data :";
    for (unsigned int i = 0; i < sensorData.nStations; i++) {
        std::cout << "\t" << sensorData.data[0][i];
    }
    std::cout << std::endl;

    // Simple Shepard interpolator
    const unsigned int gridWidth = 250u;
    const unsigned int gridHeight = 250u;
    const unsigned int pixels = gridHeight*gridWidth;
    const float shepardMu = 2.0f;

    SimpleShepardInterpolator<int,float> ssInterpolator(shepardMu);
    log_console->infoStream() << "Interpolating with the Simple Shepard Method...";
    float *interpolatedGrid = ssInterpolator(gridWidth,gridHeight,sensorData.nStations, sensorData.x, sensorData.y, sensorData.data[0]);

    // Create Colorizer
    const ColorRGB red(255u,0u,0u);
    const ColorRGB blue(0u,0u,255u);
    LinearColorizer<float,ColorRGB> colorizer(pixels,interpolatedGrid,red,blue);
    
    // Generate image
    log_console->infoStream() << "Generating image...";
    ImageGenerator::generateImage<float,ColorRGB>(gridWidth, gridHeight, interpolatedGrid, colorizer,
            "img/","test","png");

    // Clean up
    delete [] interpolatedGrid;

    return EXIT_SUCCESS;
}
