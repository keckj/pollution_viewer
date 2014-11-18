
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <ctime>
#include <boost/regex.hpp>

#include "log.hpp"
#include "dataParser.hpp"

DataParser::DataParser() {
}

DataParser::~DataParser() {
}

void DataParser::parseSensorData(std::string fileName, std::map<std::string, Station*> targetStations) {

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
    unsigned int nExpectedValues = 0;
    unsigned int nMatchedStations = 0;

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
            log_console->infoStream() << "[DataParser] "
                << "\tInterval   : " << date;
            delete [] date;
            parsedInterval = true;
        }
        else if(boost::regex_match(line, match, stationRegexp)) {
            log_console->debugStream() << "[DataParser] " << "\t\tStation " << match[0];
            std::string stationKey, stationName, stationType;
    
            stationKey = match[0];
            stationName = match[1];
            stationType = match[2];

            if(parsedParameters) {
                if(targetStations.find(stationKey) == targetStations.end()) {
                    log_console->warnStream() << "[DataParser] Sensor data skipped because " << stationKey << " is not a known station !";
                    continue;
                }

                getline(infile,line);
                
                const boost::regex matchVal("([0-9]+)|-");
                unsigned int nData = 0;
                int *sensorValues = new int[nExpectedValues];

                boost::sregex_token_iterator it(line.begin(), line.end(), matchVal);
                boost::sregex_token_iterator end;

                for(;it != end; ++it) {
                    if(nData == nExpectedValues) {
                        log_console->warnStream() << "[DataParser] At station " << stationName << " - " << stationType
                            << "\n\t\t\t\tParsed more than " << nData << " sensor values but only " << nExpectedValues << " were expected !";
                    }

                    if(*it == '-')
                        sensorValues[nData] = -1;
                    else
                        sensorValues[nData] = std::stoi(*it);
                    
                    nData++;
                }
              
                if(nData < nExpectedValues) {
                    log_console->warnStream() << "[DataParser] At station " << stationName << " - " << stationType
                        << "\n\t\t\t\tParsed " << nData << " sensor values but exactly " << nExpectedValues << " were expected !";
                }
            
                SensorData<int> sensorData(sensorName, sensorUnit, startDate, endDate, interval, nData, sensorValues);
                targetStations.at(stationKey)->addSensorData(sensorData);

                nMatchedStations++;
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
                nExpectedValues = (mktime(&endDate) - mktime(&startDate))/(interval.tm_hour*3600+interval.tm_min*60+interval.tm_sec) + 1;
                log_console->infoStream() << "[DataParser] "
                    << "\tExpected sensor values based on interval: " << nExpectedValues;
            }
        }
    }

    log_console->infoStream() << "[DataParser] "
        << "Successfully parsed " << nMatchedStations << " station sensor data !";
    
}

SensorDataArray<int> buildSensorDataArray(std::map<std::string, Station*> stations, const std::string &targetSensorName) {
    
    std::string unitName;
    std::tm startTime, endTime,deltaT;
    unsigned int nMeasures = 0u;

    memset(&startTime, 0, sizeof(std::tm));
    memset(&endTime, 0, sizeof(std::tm));
    memset(&deltaT, 0, sizeof(std::tm));

    const std::string **stationNames;
    StationType *stationTypes;
    double *x;
    double *y;
    double *z;
    int **data;

    //check the number of stations that have this sensor and get basic sensor data
    unsigned int nStations = 0;
    for(auto &station : stations) {
        if (station.second->hasSensorData(targetSensorName)) {

            SensorData<int> sensorData = station.second->getSensorData(targetSensorName);

            if(nStations == 0) {
                unitName = sensorData.unitName;
                startTime = sensorData.startTime;
                endTime = sensorData.endTime;
                deltaT = sensorData.deltaT;
                nMeasures = sensorData.nData;
            }
            else { //check if data is coherant
                assert(nMeasures == sensorData.nData);
            }

            nStations++;
        }
    }
    
    //allocate arrays
    stationNames = new const std::string*[nStations];
    stationTypes = new StationType[nStations];
    x = new double[nStations];
    y = new double[nStations];
    z = new double[nStations];
    
    data = new int*[nMeasures];
    for (unsigned int i = 0; i < nMeasures; i++) {
        data[i] = new int[nStations];
    }

    //fill arrays
    unsigned int count = 0;
    for(auto &station : stations) {
        if (station.second->hasSensorData(targetSensorName)) {
             SensorData<int> sensorData = station.second->getSensorData(targetSensorName);
             stationNames[count] = &(station.second->name);
             stationTypes[count] = station.second->type;
             x[count] = station.second->location.x;
             y[count] = station.second->location.y;
             z[count] = station.second->location.z;
             for (unsigned int i = 0; i < nMeasures; i++) {
                 data[i][count] = sensorData.data[i];
             }
             count++;
        }
    }
    
    //build structure and return 
    return SensorDataArray<int>(targetSensorName, unitName, startTime, endTime, deltaT, nMeasures, nStations,
            stationNames, stationTypes, x, y, z, data);

}
