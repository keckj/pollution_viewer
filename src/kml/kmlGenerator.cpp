

#include "kmlUtils.hpp"
#include "kmlGenerator.hpp"

namespace KmlGenerator {

    KmlGenerator::KmlGenerator(const SensorDataArr &sensorData,
            const InterpData &interpData,
            const IsoLines &isolines, 
            const IsoContours &isocontours) :
        KmlFile(kmlFolder+kmlFileName),
        sensorData(sensorData),
        interpData(interpData),
        isolines(isolines),
        isocontours(isocontours)
    {

        generateKmlFile();
    }

    KmlGenerator::~KmlGenerator() {
    }

    void KmlGenerator::generateKmlFile() {

        putKmlHeader();

        // Styles definition
        putStationStyle();
        putIsoLineStyles();
        putIsoContourStyles();

        // Initial camera position
        putInitialView();

        // Station placemarks
        putStations();

        unsigned int k = 0;
        for(const auto &interpolator : interpData) {
            const std::string &interpolatorName = interpolator.first;

            putFolder(interpolatorName, "Interpolator "+std::to_string(k)+": "+interpolatorName, false, false);
       
            // Ground overlays folder
            putInterpolatedDataOverlays(interpolatorName);
        
            // Ground overlays
            putScreenOverlays(interpolatorName);

            // Isolines and contours
            putIsoLines(interpolatorName);
            putIsoContours(interpolatorName);

            endFolder();
            k++;
        }
        
        
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
        putIconStyle(stationIconHref, Offset(), 0.25f, 0.0f);        //custom icon
        endStyle();
        skipLine();
    }

    void KmlGenerator::putIsoLineStyles() {

        std::map<std::string, bool> styles;

        for (const auto &interpIsolines : isolines) {
            for(const auto &temporalIsolines : interpIsolines.second) {
                for(const auto &isoline : temporalIsolines) {
                    std::string styleName = "IsoLine_" + isoline.lines.color.toHexString();
                    if(styles.find(styleName) == styles.end()) {
                        startStyle(styleName);
                        putLineStyle(isoline.lines.color, NORMAL, 2u);
                        endStyle();
                        styles.emplace(styleName, true);
                    }
                }
            }
        }
        skipLine();
    }

    void KmlGenerator::putIsoContourStyles() {

        std::map<std::string, bool> styles;

        for (const auto &interpIsocontours : isocontours) {
            for(const auto &temporalIsocontours : interpIsocontours.second) {
                for(const auto &isocontour : temporalIsocontours) {
                    std::string styleName = "IsoContour_" + isocontour.color.toHexString();
                    if(styles.find(styleName) == styles.end()) {
                        startStyle(styleName);
                        putPolyStyle(isocontour.color, NORMAL, true, true);
                        putLineStyle(ColorRGBA::black, NORMAL, 1u);
                        endStyle();
                        styles.emplace(styleName, true);
                    }
                }
            }
        }

        skipLine();
    }

    void KmlGenerator::putInitialView() {
        putLookAt((sensorData.bbox.xmin+sensorData.bbox.xmax)/2.0, (0.75*sensorData.bbox.ymin+0.25*sensorData.bbox.ymax), 0.0, CLAMP_TO_GROUND, 250000.0, 30.0f, -20.0f);
        skipLine();
    }

    void KmlGenerator::putScreenOverlays(const std::string &interpolatorName) {
        
        const unsigned int nData = std::min(maxDataProcessed, sensorData.nMeasures);
        putFolder("GUI", "Screen Overlays (" + interpolatorName + ")", false, true);
    
        for (unsigned int i = 0; i < nData; i++) {
            putScreenOverlay("Color scale " + std::to_string(i), "",
                    Offset(0.0f, 0.0f),
                    Offset(0.1f, 0.15f),
                    Offset(0.0f, 400, PIXELS),
                    Offset(),
                    0.0f, 3, 
                    screenOverlayFolder+screenOverlayPrefix+interpolatorName+"_"+std::to_string(i)+"."+screenOverlayImgExt,
                    defaultVisibleInterpolatorId.compare(interpolatorName) == 0,
                    sensorData.getTime(i),
                    sensorData.getTime(i+1, true)
                    );

        }
        endFolder();
        skipLine();
    }

    void KmlGenerator::putInterpolatedDataOverlays(const std::string &interpolatorName) {
        const unsigned int nData = std::min(maxDataProcessed, sensorData.nMeasures);
        putFolder("Interpolation results", "Data Overlays ("+interpolatorName+")", false, true);
        for (unsigned int i = 0; i < nData; i++) {
            putGroundOverlay("Data"+std::to_string(i), 
                    0u, CLAMP_TO_GROUND, 
                    sensorData.bbox, 
                    0.0, 
                    groundOverlayFolder+groundOverlayPrefix+interpolatorName+"_"+std::to_string(i)+"."+groundOverlayImgExt,
                    defaultVisibleInterpolatorId.compare(interpolatorName) == 0,
                    sensorData.getTime(i), 
                    sensorData.getTime(i+1, true)
                    );
        }
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

    void KmlGenerator::putIsoLines(const std::string &interpolatorName) {
        
        const unsigned int nData = std::min(maxDataProcessed, sensorData.nMeasures);
        const std::vector<IsoLineList<double,4u,float>> &interpIsolines = isolines.at(interpolatorName);

        putFolder("Isolines", "Data isolines (" + interpolatorName + ")", false, true);
        
        unsigned int j = 0;
        for(const auto &temporalIsolines : interpIsolines) {
            unsigned int i = 1;
            for(const auto &isoline : temporalIsolines) {
                putColorLineStrings("Isolines level " + std::to_string(i++), 
                        "Isovalue: " + std::to_string(isoline.value) + " mg/m³",
                        "IsoLine_", 
                        isoline.lines,
                        defaultVisibleInterpolatorId.compare(interpolatorName) == 0,
                        sensorData.getTime(j), 
                        sensorData.getTime(j+1, true)
                    );
            }
            j++;
        }

        endFolder();
        skipLine();
    }

    void KmlGenerator::putIsoContours(const std::string &interpolatorName) {
        
        const unsigned int nData = std::min(maxDataProcessed, sensorData.nMeasures);
        const std::vector<IsoContourList<double,4u,float>> &interpIsocontours = isocontours.at(interpolatorName);

        putFolder("Isocontours", "Data isocontours (" + interpolatorName + ")", false, false);
        
        unsigned int j = 0;
        for(const auto &temporalIsocontours : interpIsocontours) {
            unsigned int i = 1;
            for(auto isocontour = std::next(temporalIsocontours.begin()); isocontour != temporalIsocontours.end(); ++isocontour) {
                auto prev = std::prev(isocontour);
                putColorPolygons("Isocontour level " + std::to_string(i++), 
                        "Min value: " + std::to_string(isocontour->lowerValue) + " mg/m³\n"
                        "Max value: " + std::to_string(isocontour->upperValue) + " mg/m³", 
                        "IsoContour_", 
                        ColorMultiLine<double,4u>(isocontour->lines, isocontour->color),
                        ColorMultiLine<double,4u>(prev->lines, prev->color),
                        false,
                        sensorData.getTime(j), 
                        sensorData.getTime(j+1, true),
                        ABSOLUTE
                    );
            }
            j++;
        }

        endFolder();
        skipLine();
    }

}
