
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

    std::string line;
    const std::regex stationRegexp("([A-Z])(.*)", std::regex::extended);

    while (infile.good()){
        getline(infile,line);
        log_console->infoStream() << "Parsing line: " << line;
        std::smatch match;
        if(std::regex_match(std::string(line), match, stationRegexp)) { 
            std::cout << "the matches were: ";
            std::cout << "[" << match[1] << "]";
            std::cout << "[" << match[2] << "]";
            std::cout << std::endl;
        }
    }

    return std::map<std::string,Station>();
}
