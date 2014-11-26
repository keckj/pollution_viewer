
#ifndef MAINFUNCS_H
#define MAINFUNCS_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <map>
#include <vector>

#include "log.hpp"
#include "stationParser.hpp"
#include "dataParser.hpp"
#include "overlayGenerator.hpp"
#include "isolineGenerator.hpp"
#include "kmlGenerator.hpp"
#include "config.hpp"
    
namespace mainFuncs {
    using namespace Globals;

    using SensorDataArr = SensorDataArray<int>;
    using InterpData    = std::map<std::string, std::vector< InterpolatedData<float>>>;
    using IsoLines      = std::map<std::string, std::vector< IsoLineList     <double,4u,float>>>;
    using IsoContours   = std::map<std::string, std::vector< IsoContourList  <double,4u,float>>>;

    void init();
    void generateScreenOverlays(const SensorDataArr &, const InterpData &);
    void generateGroundOverlays(const SensorDataArr &, const InterpData &);
    void generateKmlFile(const SensorDataArr &, const InterpData &, const IsoLines &, const IsoContours &);
    //void clean(SensorDataArr &, InterpData &);

    SensorDataArr parseSensorData();
    InterpData interpolateData(const SensorDataArr &);

    IsoLines generateIsolines(const SensorDataArr &, const InterpData &);
    IsoContours generateIsocontours(const SensorDataArr &, const InterpData &, const IsoLines &);
}

#endif /* end of include guard: MAINFUNCS_H */
