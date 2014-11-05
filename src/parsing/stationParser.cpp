
#include <iostream>
#include <fstream>
#include <boost/regex.hpp>

#include "log.hpp"
#include "vec.hpp"
#include "stationType.hpp"
#include "stationParser.hpp"

StationParser::StationParser() {}
StationParser::~StationParser() {}

std::map<std::string, Station> StationParser::parse(std::string fileName) {

    using log4cpp::log_console;

    log_console->infoStream() << "[StationParser] Parsing file " << fileName << "...";

    std::ifstream infile;
    infile.open(fileName);

    if(infile.bad() || infile.fail()) {
        log_console->errorStream() << "[StationParser] Error while loading file" << fileName << " !";
        exit(EXIT_FAILURE);
    }
    
    const boost::regex stationRegexp("^([^0-9-].*) - ([^-]*)$", boost::regex::extended);
    const boost::regex coordinatesRegexp("^([0-9]+\\.[0-9]+) ([0-9]+\\.[0-9]+) ([0-9]+\\.[0-9]+)$");

    std::string line;
    boost::smatch stationMatch, coordinateMatch;
    std::map<std::string,Station> stations;

    while (infile.good()){
        getline(infile,line);
        if(boost::regex_match(line, stationMatch, stationRegexp)) {
            std::string stationName = stationMatch[1];
            std::string stationType = stationMatch[2];
            getline(infile,line);
            if(boost::regex_match(line,coordinateMatch, coordinatesRegexp)) {
                double x = std::stod(coordinateMatch[1]);
                double y = std::stod(coordinateMatch[2]);
                double z = std::stod(coordinateMatch[3]);

                Station station(stationName, stationType, Vec<double>(x,y,z));
                
                log_console->debugStream() << "[StationParser] "
                    << stationName << " (" << stationType << ")"
                    << " at (" << x << "," << y << "," << z << ")";
                
                if(stations.find(stationName+" - "+stationType) == stations.end()) {
                    stations.insert(std::pair<std::string,Station>(stationName+" - "+stationType, station));
                }
                else {
                    log_console->warnStream()
                        << "Skipping station '" << stationName << "' with type '" << stationType 
                        << "' because it was already parsed before !";
                }

            }
            else {
                log_console->warnStream()
                    << "Skipping station '" << stationName << "' with type '" << stationType 
                    << "' because no coordinates were found !";
            }
        }
    }
                
    log_console->infoStream() << "[StationParser] "
        << "Successfully parsed " << stations.size() << " stations !";

    return stations;
}
