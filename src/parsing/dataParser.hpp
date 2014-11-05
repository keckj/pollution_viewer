
#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <map>
#include <string>

#include "station.hpp"

class DataParser {
    public:
        DataParser();
        ~DataParser();

        void parseSensorData(std::string fileName, std::map<std::string, Station> targetStations);
};

#endif /* end of include guard: DATAPARSER_H */
