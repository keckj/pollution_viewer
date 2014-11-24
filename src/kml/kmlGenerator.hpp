
#ifndef KMLGENERATOR_H
#define KMLGENERATOR_H

#include "kmlFile.hpp"
#include "sensorDataArray.hpp"
#include "isolineUtils.hpp"
#include "isoline.hpp"
#include "isocontour.hpp"

class KmlGenerator final : public KmlFile {
    public:
        KmlGenerator(const std::string &filePath, 
                     const std::string &screenOverlayFolder,
                     const std::string &screenOverlayPrefix,
                     const std::string &screenOverlaySuffix,
                     const std::string &groundOverlayFolder,
                     const std::string &groundOverlayPrefix,
                     const std::string &groundOverlaySuffix,
                     const std::string &stationIconPath,
                     const SensorDataArray<int> &sensorData,
                     const IsoLineList<double,4u,float> &isolines,
                     const IsoContourList<double,4u,float> &isocontours);

        ~KmlGenerator();

    private:
        void generateKmlFile();

        void putKmlHeader();
        void putStationStyle();
        void putIsoLineStyles();
        void putIsoContourStyles();
        void putScreenOverlays();
        void putInitialView();
        void putStations();
        void putIsoLines();
        void putIsoContours();
        void putInterpolatedDataOverlays();
        void putKmlFooter();
        
        const std::string &screenOverlayFolder;
        const std::string &screenOverlayPrefix;
        const std::string &screenOverlaySuffix;
        const std::string &groundOverlayFolder;
        const std::string &groundOverlayPrefix;
        const std::string &groundOverlaySuffix;
        const std::string &stationIconPath;
        const SensorDataArray<int> &sensorData;
        const IsoLineList<double,4u,float> &isolines;
        const IsoContourList<double,4u,float> &isocontours;
};

#endif /* end of include guard: KMLGENERATOR_H */
