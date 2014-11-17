

#include <iostream>
#include <cassert>
#include <cstdlib>

#include "log.hpp"

#include "stationParser.hpp"
#include "dataParser.hpp"
#include "simpleShepardInterpolator.hpp"

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

    //change data layout of a given sensor (AoS to SaO)
    const std::string sensorName("Particules PM10");
    SensorDataArray<int> sensorData = buildSensorDataArray(stations, sensorName);

    //print data of the first hour
    for (unsigned int i = 0; i < sensorData.nStations; i++) {
        std::cout << "\t" << sensorData.data[0][i];
    }

    //test gogo interpolator
    SimpleShepardInterpolator<int,float> ssInterpolator(2.0f);
    float *interpolatedGrid = ssInterpolator(32,32,sensorData.nStations, sensorData.x, sensorData.y, sensorData.data[0]);

        std::cout << std::endl;
        std::cout << std::endl;
    for (unsigned int j = 0; j < 32; j++) {
        for (unsigned int i = 0; i < 32; i++) {
            std::cout << "\t" << interpolatedGrid[j*32+i];
        }
        std::cout << std::endl;
    }


    return EXIT_SUCCESS;
}
