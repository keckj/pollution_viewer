
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
#include "kmlFile.hpp"

int main(int argc, char** argv) {

    /////////////// KML TEST ////////////////
    KmlFile kml("test.kml");
    kml.startKml();
    kml.startDocument();
    kml.startPlacemark();
    kml.putName("TEST FILE");
    kml.putVisibility(true);
    kml.putDescription("Just a simple test file !");
    kml.startStyle();
    kml.putColor(ColorRGBA(0xf0,0x08,0x04,0x02));
    kml.endStyle();
    kml.endPlacemark();
    kml.endDocument();
    kml.endKml();
    
    //return EXIT_SUCCESS;
    ////////////////////////////////////////////
    
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

    // Simple Shepard interpolator
    const unsigned int gridWidth = 512u;
    const unsigned int gridHeight = 512u;
    const unsigned int pixels = gridHeight*gridWidth;
    const float shepardMu = 2.0f;

    SimpleShepardInterpolator<int,float> ssInterpolator(shepardMu);
    log_console->infoStream() << "Interpolating with the Simple Shepard Method...";
    float *interpolatedGrid = ssInterpolator(gridWidth,gridHeight,sensorData.nStations, sensorData.x, sensorData.y, sensorData.data[0]);

    // Create Colorizer
    const ColorRGB red(255u,0u,0u);
    const ColorRGB blue(0u,0u,255u);
    LinearColorizer<float,ColorRGB> colorizer(pixels,interpolatedGrid,red,blue);
    
    //const ColorMonochrome black(0u);
    //const ColorMonochrome white(255u);
    //LinearColorizer<float,ColorMonochrome> colorizer(pixels,interpolatedGrid,black,white);
    
    // Generate image
    log_console->infoStream() << "Generating image...";
    ImageGenerator::generateImage<float,ColorRGB>(gridWidth, gridHeight, interpolatedGrid, colorizer,
            "img/","test","png");

    // Clean up
    log_console->infoStream() << "Done ! Cleaning Up...";
    delete [] interpolatedGrid;

    return EXIT_SUCCESS;
}
