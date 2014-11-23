
#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstdlib>
#include <ctime>


#include "log.hpp"
#include "stationParser.hpp"
#include "dataParser.hpp"
#include "simpleShepardInterpolator.hpp"
#include "linearColorizer.hpp"
#include "overlayGenerator.hpp"
#include "isolineGenerator.hpp"
#include "kmlGenerator.hpp"


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
    
    // Simple Shepard interpolator
    const unsigned int gridWidth = 256u;
    const unsigned int gridHeight = 256u;
    const unsigned int pixels = gridHeight*gridWidth;
    const float shepardMu = 2.0f;

    SimpleShepardInterpolator<int,float> ssInterpolator(shepardMu);
    log_console->infoStream() << "Interpolating with the Simple Shepard Method...";
    const InterpolatedData<float> &interpolatedGrid = ssInterpolator(gridWidth,gridHeight,sensorData.nStations, sensorData.x, sensorData.y, sensorData.data[0]);

    // Create Data Colorizer
    const ColorRGBA red(255u,0u,0u,255u);
    const ColorRGBA blue(0u,0u,255u,50u);
    LinearColorizer<float,4u> dataColorizer(interpolatedGrid,red,blue);
    
    // Generate ground overlay
    log_console->infoStream() << "Generating image...";
    OverlayGenerator::generateImage<float,4u>(interpolatedGrid, dataColorizer, "img/","test","png");

    // Create Isoline Colorizer
    LinearColorizer<float,4u> isolineColorizer(interpolatedGrid,ColorRGBA::blue,ColorRGBA::red);
    
    // Generate isolines
    IsoLineGenerator<float,4u> isolineGenerator(sensorData.bbox);
    const IsoLineList<double,4u,float> &isolines = isolineGenerator.generateIsolines(interpolatedGrid, 10, isolineColorizer);

    // Generate Color Overlay
    dataColorizer.generateColorRange();

    // Clean up
    log_console->infoStream() << "Done ! Cleaning Up...";
    delete [] interpolatedGrid.density;

    // generate KML file
    KmlGenerator kml("test.kml",
                     "kml/screenOverlays/", "screen_", ".png",
                     "kml/groundOverlays/", "ground_", ".png",
                     "kml/icons/station.png",
                     sensorData,
                     isolines);
    
    return EXIT_SUCCESS;
}
