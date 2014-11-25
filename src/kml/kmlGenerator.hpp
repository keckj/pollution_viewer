
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
    using InterpData    = InterpolatedData<float>;
    using IsoLines      = IsoLineList     <double,4u,float>;
    using IsoContours   = IsoContourList  <double,4u,float>;

    class KmlGenerator final : public KmlFile {


        public:
            KmlGenerator(const SensorDataArr &sensorData,
                    const IsoLines &isolines,
                    const IsoContours &isocontours);

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

            const SensorDataArr &sensorData;
            const IsoLines &isolines;
            const IsoContours &isocontours;
    };
}

#endif /* end of include guard: KMLGENERATOR_H */
