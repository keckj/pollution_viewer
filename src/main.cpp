

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

    StationParser sp;
    std::map<std::string,Station> stations = sp.parse("data/stations.data");

    DataParser dp;
    dp.parseSensorData("data/particules.data", stations);

    return EXIT_SUCCESS;
}
