
#ifndef STATIONPARSER_H
#define STATIONPARSER_H

#include <map>
#include <string>

#include "station.hpp"

class StationParser {

    public:
        StationParser();
        ~StationParser();

        std::map<std::string, Station> parse(std::string fileName);
};

#endif /* end of include guard: STATIONPARSER_H */
