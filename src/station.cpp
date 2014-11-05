
#include "station.hpp"
#include "sensorData.hpp"
#include "log.hpp"

Station::Station(std::string name, StationType type, Vec<double> location) : 
    name(name), type(type), location(location)
{
}
        
void Station::addSensorData(SensorData<float> data) {
    if(_data.find(data.sensorName) == _data.end()) {
        _data.insert(std::pair<std::string,SensorData<float>>(data.sensorName, data));
    }
    else {
        log4cpp::log_console->warnStream() << "Sensor data ignored because " << data.sensorName << " was already added !";
    }
}

SensorData<float>& Station::getSensorData(std::string sensorName) {
    if(_data.find(sensorName) == _data.end()) {
        log4cpp::log_console->errorStream() << "Sensor data " << sensorName << " requested but it was not added !";
        exit(EXIT_FAILURE);
    }
    else {
        return _data.at(sensorName);
    }
}

