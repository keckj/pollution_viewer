
#include <iostream>
#include <fstream>
#include <regex>

#include "log.hpp"
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

    std::regex stationRegexp("(.*) - (.*)");
    std::string line;

    while (infile.good()){
        getline(infile, line);
        log_console->infoStream() << "Parsing line: " << line;
        std::smatch match;
        std::regex_match(line, match, stationRegexp);
        if(!match.empty())
            log_console->infoStream() << "\tMatched '" << match[1] << "' and '" << match[2] << "' !";
    }

    return std::map<std::string,Station>();
}
