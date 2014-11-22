
#include "kmlGenerator.hpp"
        
KmlGenerator::KmlGenerator(const std::string &filePath, 
        const std::string &screenOverlayFolder,
        const std::string &screenOverlayPrefix,
        const std::string &screenOverlaySuffix,
        const std::string &groundOverlayFolder,
        const std::string &groundOverlayPrefix,
        const std::string &groundOverlaySuffix,
        const std::string &stationIconPath,
        const SensorDataArray<int> &sensorData,
        const ColorLineList<double,4u> &isolines) :
    KmlFile(filePath)
{
    
    generateKmlFile(screenOverlayFolder,
        screenOverlayPrefix,
        screenOverlaySuffix,
        groundOverlayFolder,
        groundOverlayPrefix,
        groundOverlaySuffix,
        stationIconPath,
        sensorData,
        isolines);
}

KmlGenerator::~KmlGenerator() {
}

void KmlGenerator::generateKmlFile(const std::string &screenOverlayFolder,
        const std::string &screenOverlayPrefix,
        const std::string &screenOverlaySuffix,
        const std::string &groundOverlayFolder,
        const std::string &groundOverlayPrefix,
        const std::string &groundOverlaySuffix,
        const std::string &stationIconPath,
        const SensorDataArray<int> &sensorData,
        const ColorLineList<double,4u> &isolines) {

    putKmlHeader();

    // Style definition
    startStyle("stationStyle");
    putLabelStyle(ColorRGBA(0x00,0x00,0x00,0x00), NORMAL, 0.0f); //invisible labels
    putIconStyle("http://ukmobilereview.com/wp-content/uploads/2013/07/antenna-strength.png",
            Offset(), 0.25f, 0.0f); //custom icon
    endStyle();
    skipLine();
   
    // Initial camera position
    putLookAt((sensorData.bbox.xmin+sensorData.bbox.xmax)/2.0, (0.75*sensorData.bbox.ymin+0.25*sensorData.bbox.ymax), 0.0, CLAMP_TO_GROUND, 250000.0, 30.0f, -20.0f);
    skipLine();

    // Screen overlay
    putScreenOverlay("ScreenOverlay", "Screen overlay used to display informations.",
            Offset(0.0f, 0.0f),
            Offset(0.1f, 0.15f),
            Offset(0.0f, 400, PIXELS),
            Offset(),
            0.0f, 3, "img/overlay.png");
    skipLine();
  
    // Station placemarks folder
    putFolder("Stations", "Station locations", false, true);
    for (unsigned int i = 0; i < sensorData.nStations; i++) {
        putPlaceMark(*sensorData.stationNames[i], sensorData.stationDescription(i,getCurrentIndentLevel()+2), "stationStyle", 
                sensorData.x[i], sensorData.y[i], 0.0, CLAMP_TO_GROUND);
    }
    endFolder();
    skipLine();
    
    // Isolines
    putFolder("Isolines", "Data isolines.", false, true);
    putLineStrings("Isolines", "", isolines);
    endFolder();
    skipLine();

    // Ground overlays folder
    putFolder("Sensor data overlays", "Interpolation results", false, true);
    putGroundOverlay("First hour data", 0u, CLAMP_TO_GROUND, sensorData.bbox, 0.0, "img/test.png");
    endFolder();
    skipLine();

    putKmlFooter();
    ////////////////////////////////////////////
}

void KmlGenerator::putKmlHeader() {
    time_t t = time(0);
    std::tm *now = localtime(&t);

    startKml();
    skipLine();
    putComment("=====================================================================================================================");
    putComment("This file was generated automatically with real meteorological data and is part of the Ensimag visualization project.");
    putComment("=====================================================================================================================");
    skipLine();
    startDocument("Root");
    putName("Environemental contaminant viewer");
    putDescription("PM10 particles");
    putDate(*now, YYYY_MM_DD_hh_mm_ss);
    putAuthor("Jean-Baptiste Keck");
    putAuthor("Alexandre Ribard");
    skipLine();
    putVisibility(true);
    putOpen(true);
    skipLine();
}
        
void KmlGenerator::putKmlFooter() {
    endDocument();
    endKml();
}
