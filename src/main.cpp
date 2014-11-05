

#include <iostream>
#include <cassert>
#include <cstdlib>

#include "log.hpp"

#include "stationParser.hpp"
#include "dataParser.hpp"

int main(int argc, char** argv) {

    using log4cpp::log_console;
    log4cpp::initLogs();

    std::cout << "Projet de visualisation, viens on est bien bien bien bien bien !!!" << std::endl;    

    //Parse stations
    StationParser sp;
    std::map<std::string, Station*> stations = sp.parse("data/stations.data");

    //Parse sensor data
    DataParser dp;
    dp.parseSensorData("data/particules.data", stations);

    //Get first hour data
    const std::string sensorName("Particules PM10");
    
    std::cout << sensorName << ":" << std::endl;
    for(auto &station : stations) {
        if (station.second->hasSensorData(sensorName)) {
            SensorData<int> values = station.second->getSensorData(sensorName);
            std::cout << values.data[0] << " ";
        }
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
