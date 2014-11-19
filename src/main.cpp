
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>

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
    
    //Compute bounding box
    BoundingBox<double> bbox = computeBoundingBox(Coords<double>(sensorData.nStations, sensorData.x, sensorData.y));

    // Simple Shepard interpolator
    const unsigned int gridWidth = 128u;
    const unsigned int gridHeight = 128u;
    const unsigned int pixels = gridHeight*gridWidth;
    const float shepardMu = 2.0f;

    SimpleShepardInterpolator<int,float> ssInterpolator(shepardMu);
    log_console->infoStream() << "Interpolating with the Simple Shepard Method...";
    float *interpolatedGrid = ssInterpolator(gridWidth,gridHeight,sensorData.nStations, sensorData.x, sensorData.y, sensorData.data[0]);

    // Create Colorizer
    const ColorRGBA red(255u,0u,0u,255u);
    const ColorRGBA blue(0u,0u,255u,50u);
    LinearColorizer<float,ColorRGBA> colorizer(pixels,interpolatedGrid,red,blue);
    
    //const ColorMonochrome black(0u);
    //const ColorMonochrome white(255u);
    //LinearColorizer<float,ColorMonochrome> colorizer(pixels,interpolatedGrid,black,white);
    
    // Generate image
    log_console->infoStream() << "Generating image...";
    ImageGenerator::generateImage<float,ColorRGBA>(gridWidth, gridHeight, interpolatedGrid, colorizer,
            "img/","test","png");

    // Generate Color Overlay
    colorizer.generateColorRange();

    // Clean up
    log_console->infoStream() << "Done ! Cleaning Up...";
    delete [] interpolatedGrid;

    /////////////// KML TEST ////////////////
    KmlFile kml("test.kml");
    kml.putKmlHeader();

    // Style definition
    kml.startStyle("stationStyle");
    kml.putLabelStyle(ColorRGBA(0x00,0x00,0x00,0x00), NORMAL, 0.0f); //invisible labels
    kml.putIconStyle("http://ukmobilereview.com/wp-content/uploads/2013/07/antenna-strength.png",
            HotSpot(), 0.25f, 0.0f); //custom icon
    kml.endStyle();
    kml.skipLine();
   
    // Initial camera position
    kml.putLookAt((bbox.xmin+bbox.xmax)/2.0, (0.75*bbox.ymin+0.25*bbox.ymax), 0.0, CLAMP_TO_GROUND, 250000.0, 30.0f, -20.0f);
    kml.skipLine();
  
    // Station placemarks folder
    kml.putFolder("Stations", "Station locations", false, true);
    for (unsigned int i = 0; i < sensorData.nStations; i++) {
        kml.putPlaceMark(*sensorData.stationNames[i], sensorData.stationDescription(i,kml.getCurrentIndentLevel()+2), "stationStyle", 
                sensorData.x[i], sensorData.y[i], 0.0, CLAMP_TO_GROUND);
    }
    kml.endFolder();
    kml.skipLine();

    // Ground overlays folder
    kml.putFolder("Sensor data overlays", "Interpolation results", false, true);
    kml.putGroundOverlay("First hour data", 0u, CLAMP_TO_GROUND, bbox, 0.0, "img/test.png");
    kml.endFolder();
    kml.skipLine();

    kml.putKmlFooter();
    ////////////////////////////////////////////
    
    return EXIT_SUCCESS;
}
