
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <boost/regex.hpp>

#include "log.hpp"
#include "dataParser.hpp"

DataParser::DataParser() {
}

DataParser::~DataParser() {
}

void DataParser::parseSensorData(std::string fileName, std::map<std::string, Station> targetStations) {

    using log4cpp::log_console;
    log_console->infoStream() << "[DataParser] Parsing file " << fileName << "...";

    std::ifstream infile;
    infile.open(fileName);

    if(infile.bad() || infile.fail()) {
        log_console->errorStream() << "[DataParser] Error while loading file" << fileName << " !";
        exit(EXIT_FAILURE);
    }

    const boost::regex stationRegexp("^([^0-9-].*) - ([^-]*)$", boost::regex::extended);
    const boost::regex sensorTypeRegexp("^Type\\s+=\\s+(.*)$", boost::regex::extended);
    const boost::regex sensorUnitRegexp("^Unit\\s+=\\s+(.*)$", boost::regex::extended);

    const std::string matchDate = "([0-9]\{2})/([0-9]\{2})/([0-9]\{4})";
    const std::string matchHour = "([0-9]\{2}):([0-9]\{2}):([0-9]\{2})";
    const boost::regex startDateRegexp("^StartDate\\s+=\\s+(" + matchDate + " " + matchHour + ")$", boost::regex::extended);
    const boost::regex endDateRegexp("^EndDate\\s+=\\s+(" + matchDate + " " + matchHour + ")$", boost::regex::extended);
    const boost::regex intervalRegexp("^Interval\\s+=\\s+(" + matchHour + ")$", boost::regex::extended);

    std::string line;
    boost::smatch match;

    bool parsedSensorType, parsedUnit, parsedStartDate, parsedEndDate, parsedInterval, parsedParameters;
    parsedParameters = parsedInterval = parsedEndDate = parsedStartDate = parsedUnit = parsedSensorType = false;

    std::string sensorName;
    std::string sensorUnit;
    std::tm startDate = {0,0,0,1,0,0,0,0,0,0,0};
    std::tm endDate   = {0,0,0,1,0,0,0,0,0,0,0};
    std::tm interval  = {0,0,0,1,0,0,0,0,0,0,0};
    unsigned int nData = 0;

    while (infile.good()){
        getline(infile,line);

        if(!parsedSensorType && boost::regex_match(line, match, sensorTypeRegexp)) {
            sensorName = match[1];
            log_console->infoStream() << "[DataParser] "
                << "\tSensor type: " << sensorName;
            parsedSensorType = true;
        }
        else if(!parsedUnit && boost::regex_match(line, match, sensorUnitRegexp)) {
            sensorUnit = match[1];
            log_console->infoStream() << "[DataParser] "
                << "\tSensor unit: " << sensorUnit;
            parsedUnit = true;
        }
        else if(!parsedStartDate && boost::regex_match(line, match, startDateRegexp)) {
            startDate.tm_mday  = std::stoi(match[2]);
            startDate.tm_mon   = std::stoi(match[3]) - 1;
            startDate.tm_year  = std::stoi(match[4]) - 1900;
            startDate.tm_hour  = std::stoi(match[5]);
            startDate.tm_min   = std::stoi(match[6]);
            startDate.tm_sec   = std::stoi(match[7]);

            char* date = new char[100];
            strftime(date, 100, "%d/%m/%Y %H:%M:%S", &startDate);
            log_console->infoStream() << "[DataParser] "
                << "\tStart date : " << date;
            delete [] date;
            
            parsedStartDate = true;
        }
        else if(!parsedEndDate && boost::regex_match(line, match, endDateRegexp)) {
            endDate.tm_mday  = std::stoi(match[2]);
            endDate.tm_mon   = std::stoi(match[3]) - 1;
            endDate.tm_year  = std::stoi(match[4]) - 1900;
            endDate.tm_hour  = std::stoi(match[5]);
            endDate.tm_min   = std::stoi(match[6]);
            endDate.tm_sec   = std::stoi(match[7]);

            char* date = new char[100];
            strftime(date, 100, "%d/%m/%Y %H:%M:%S", &endDate);
            log_console->infoStream() << "[DataParser] "
                << "\tEnd date   : " << date;
            delete [] date;
            parsedEndDate = true;
        }
        else if(!parsedInterval && boost::regex_match(line, match, intervalRegexp)) {
            interval.tm_hour  = std::stoi(match[2]);
            interval.tm_min   = std::stoi(match[3]);
            interval.tm_sec   = std::stoi(match[4]);

            char* date = new char[100];
            strftime(date, 100, "%H:%M:%S", &interval);
            strftime(date, 100, "%d/%m/%Y %H:%M:%S", &interval);
            log_console->infoStream() << "[DataParser] "
                << "\tInterval   : " << date;
            delete [] date;
            parsedInterval = true;
        }
        else if(boost::regex_match(line, match, stationRegexp)) {
            log_console->debugStream() << "[DataParser] " << "\t\t" << match[0];
            if(parsedParameters) {
            }
            else {
                log_console->warnStream() << "[DataParser] "
                    << "Station " << match[1] << " data skipped because it was parsed before sensor parameters !";
            }
        }
        
        if(!parsedParameters) {
            parsedParameters = parsedSensorType && parsedUnit && parsedStartDate && parsedEndDate && parsedInterval;
            if(parsedParameters) {
                log_console->infoStream() << "[DataParser] "
                    << "\tAll parameters have been parsed !";
                nData = (mktime(&endDate) - mktime(&startDate))/(interval.tm_hour*3600+interval.tm_min*60+interval.tm_sec);
                log_console->infoStream() << "[DataParser] "
                    << "\tExpected data count : " << nData;
            }
        }
    }
}
