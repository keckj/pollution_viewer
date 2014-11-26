
#include "mainFuncs.hpp"
    
int main(int argc, char** argv) {

    using namespace mainFuncs;
    std::cout << "MAIN" <<  ColorRGBA::blue << std::endl;
    
    // Initialize everything
    init();

    // Parse data
    SensorDataArr sensorData = parseSensorData();
    
    // Interpolate data
    InterpData interpolatedDataGrid = interpolateData(sensorData);
    
    // Generate isolines and isocontours
    IsoLines isolines = generateIsolines(sensorData, interpolatedDataGrid);
    IsoContours isocontours = generateIsocontours(sensorData, interpolatedDataGrid, isolines);

    // Generate images
    generateScreenOverlays(sensorData, interpolatedDataGrid);
    generateGroundOverlays(sensorData, interpolatedDataGrid);

    // Generate the Kml File
    generateKmlFile(sensorData, interpolatedDataGrid, isolines, isocontours);

    // Clean Up
    //clean(sensorData, interpolatedDataGrid);

    return EXIT_SUCCESS;
}

