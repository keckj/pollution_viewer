

#include <iostream>
#include <cassert>
#include <cstdlib>

#include "log.hpp"
#include "stationParser.hpp"

int main(int argc, char** argv) {

    using log4cpp::log_console;
    log4cpp::initLogs();

    std::cout << "Projet de visualisation, viens on est bien bien bien bien bien !!!" << std::endl;    

    log_console->critStream() << "Bien bien bien !";
    log_console->errorStream() << "Bien bien bien !";
    log_console->warnStream() << "Bien bien bien !";
    log_console->infoStream() << "Bien bien bien !";
    log_console->debugStream() << "Bien bien bien !";
    
    StationParser sp;
    sp.parse("data/stations.data");


    return EXIT_SUCCESS;
}
