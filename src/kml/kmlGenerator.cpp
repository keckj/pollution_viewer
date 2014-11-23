
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
        const IsoLineList<double,4u,float> &isolines) :
    KmlFile(filePath),
    screenOverlayFolder(screenOverlayFolder),
    screenOverlayPrefix(screenOverlayPrefix),
    screenOverlaySuffix(screenOverlaySuffix),
    groundOverlayFolder(groundOverlayFolder),
    groundOverlayPrefix(groundOverlayPrefix),
    groundOverlaySuffix(groundOverlaySuffix),
    stationIconPath(stationIconPath),
    sensorData(sensorData),
    isolines(isolines)
{

    generateKmlFile();
}

KmlGenerator::~KmlGenerator() {
}

void KmlGenerator::generateKmlFile() {

    putKmlHeader();

    // Styles definition
    putStationStyle();
    putIsolineStyles();

    // Ground overlays
    putScreenOverlays();

    // Initial camera position
    putInitialView();

    // Station placemarks
    putStations();

    // Isolines
    putIsoLines();

    // Ground overlays folder
    putInterpolatedDataOverlays();

    putKmlFooter();
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

void KmlGenerator::putStationStyle() {
    startStyle("StationStyle");
    putLabelStyle(ColorRGBA(0x00,0x00,0x00,0x00), NORMAL, 0.0f); //invisible labels
    putIconStyle("http://ukmobilereview.com/wp-content/uploads/2013/07/antenna-strength.png",
            Offset(), 0.25f, 0.0f); //custom icon
    endStyle();
    skipLine();
}

void KmlGenerator::putIsolineStyles() {
    for (auto &isoline : isolines) {
        startStyle("ColorLine_" + isoline.lines.color.toHexString());
        putLineStyle(isoline.lines.color, NORMAL, 2u);
        endStyle();
    }
    skipLine();
}

void KmlGenerator::putInitialView() {
    putLookAt((sensorData.bbox.xmin+sensorData.bbox.xmax)/2.0, (0.75*sensorData.bbox.ymin+0.25*sensorData.bbox.ymax), 0.0, CLAMP_TO_GROUND, 250000.0, 30.0f, -20.0f);
    skipLine();
}

void KmlGenerator::putScreenOverlays() {
    putScreenOverlay("Color scale", "",
            Offset(0.0f, 0.0f),
            Offset(0.1f, 0.15f),
            Offset(0.0f, 400, PIXELS),
            Offset(),
            0.0f, 3, "img/overlay.png");
    skipLine();
}

void KmlGenerator::putInterpolatedDataOverlays() {
    putFolder("Sensor data overlays", "Interpolation results", false, true);
    putGroundOverlay("First hour data", 0u, CLAMP_TO_GROUND, sensorData.bbox, 0.0, "img/test.png");
    endFolder();
    skipLine();
}

void KmlGenerator::putStations() {
    putFolder("Stations", "Station locations", false, true);
    for (unsigned int i = 0; i < sensorData.nStations; i++) {
        putPlaceMark(*sensorData.stationNames[i], sensorData.stationDescription(i,getCurrentIndentLevel()+2), "StationStyle", 
                sensorData.x[i], sensorData.y[i], 0.0, CLAMP_TO_GROUND);
    }
    endFolder();
    skipLine();
}

void KmlGenerator::putIsoLines() {
    putFolder("Isolines", "Data isolines.", false, true);
    unsigned int i = 1;
    for(auto &isoline : isolines) {
        putColorLineStrings("Isolines level " + std::to_string(i++), "Isovalue: " + std::to_string(isoline.value), isoline.lines);
    }
    endFolder();
    skipLine();
}
