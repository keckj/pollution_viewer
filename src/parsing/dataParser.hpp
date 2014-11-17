
#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <map>
#include <string>

#include "station.hpp"
#include "sensorDataArray.hpp"

class DataParser {
    public:
        DataParser();
        ~DataParser();

        void parseSensorData(std::string fileName, std::map<std::string, Station*> targetStations);
};


SensorDataArray<int> buildSensorDataArray(std::map<std::string, Station*> stations, const std::string &targetSensorName);

#endif /* end of include guard: DATAPARSER_H */
