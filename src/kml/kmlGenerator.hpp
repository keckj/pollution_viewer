
#ifndef KMLGENERATOR_H
#define KMLGENERATOR_H

#include "kmlFile.hpp"
#include "sensorDataArray.hpp"
#include "isolineUtils.hpp"
#include "isoline.hpp"
#include "isocontour.hpp"
#include "config.hpp"
#include "mainFuncs.hpp"

namespace KmlGenerator {
    using namespace Globals;
    
    using SensorDataArr = SensorDataArray<int>;
    using InterpData    = std::map<std::string, std::vector< InterpolatedData<float>>>;
    using IsoLines      = std::map<std::string, std::vector< IsoLineList     <double,4u,float>>>;
    using IsoContours   = std::map<std::string, std::vector< IsoContourList  <double,4u,float>>>;

    class KmlGenerator final : public KmlFile {


        public:
            KmlGenerator(const SensorDataArr &sensorData,
                    const InterpData &interpData,
                    const IsoLines &isolines,
                    const IsoContours &isocontours);

            ~KmlGenerator();

        private:
            void generateKmlFile();

            void putKmlHeader();
            void putStationStyle();
            void putIsoLineStyles();
            void putIsoContourStyles();
            void putStations();
            void putInitialView();
            void putKmlFooter();

            void putScreenOverlays(const std::string &interpolatorName, unsigned int nData);
            void putInterpolatedDataOverlays(const std::string &interpolatorName, unsigned int nData);
            void putIsoLines(const std::string &interpolatorName, unsigned int nData);
            void putIsoContours(const std::string &interpolatorName, unsigned int nData);

            const SensorDataArr &sensorData;
            const InterpData &interpData;
            const IsoLines &isolines;
            const IsoContours &isocontours;
    };
}

#endif /* end of include guard: KMLGENERATOR_H */
