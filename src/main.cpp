

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <regex>

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

    std::string target("baaaby");
    std::smatch sm;
 
    std::regex re1("a(a)*b");
    std::regex_search(target, sm, re1);
    std::cout << "entire match: " << sm[0] << std::endl
              << "submatch #1: " << sm[1] << std::endl;
 
    std::regex re2("a(a*)b");
    std::regex_search(target, sm, re2);
    std::cout << "entire match: " << sm[0] << std::endl
              << "submatch #1: " << sm[1] << std::endl;

    //StationParser sp;
    //sp.parse("data/stations.data");

    return EXIT_SUCCESS;
}
