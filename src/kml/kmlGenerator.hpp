
#ifndef KMLGENERATOR_H
#define KMLGENERATOR_H

#include "kmlFile.hpp"
#include "sensorDataArray.hpp"
#include "isolineUtils.hpp"

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
                     const ColorLineList<double,4u> &isolines);

        ~KmlGenerator();

    private:
        void generateKmlFile(const std::string &screenOverlayFolder,
                     const std::string &screenOverlayPrefix,
                     const std::string &screenOverlaySuffix,
                     const std::string &groundOverlayFolder,
                     const std::string &groundOverlayPrefix,
                     const std::string &groundOverlaySuffix,
                     const std::string &stationIconPath,
                     const SensorDataArray<int> &sensorData,
                     const ColorLineList<double,4u> &isolines);

        void putKmlHeader();
        void putKmlFooter();
};

#endif /* end of include guard: KMLGENERATOR_H */
