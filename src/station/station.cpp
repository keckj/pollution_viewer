
#include "station.hpp"
#include "sensorData.hpp"
#include "log.hpp"

Station::Station(std::string name, StationType type, Vec<double> location) : 
    name(name), type(type), location(location)
{
}
        
bool Station::hasSensorData(std::string sensorName) const {
    return _data.find(sensorName) != _data.end();
}

void Station::addSensorData(SensorData<int> data) {
    if(hasSensorData(data.sensorName)) {
        log4cpp::log_console->warnStream() << "Sensor data ignored because " << data.sensorName << " was already added !";
    }
    else {
        _data.insert(std::pair<std::string,SensorData<int>>(data.sensorName, data));
    }
}
        
SensorData<int> Station::getSensorData(std::string sensorName) {
    if(hasSensorData(sensorName)) {
        return _data.at(sensorName);
    }
    else {
        log4cpp::log_console->errorStream() << "Sensor data " << sensorName << " requested but it was not added !";
        exit(EXIT_FAILURE);
    }
}

