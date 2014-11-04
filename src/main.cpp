

#include <iostream>
#include <cassert>
#include <cstdlib>

#include "log.hpp"

int main(int argc, char** argv) {
    std::cout << "Projet de visualisation, viens on est bien bien bien bien bien !!!" << std::endl;    

    log4cpp::log_console->critStream() << "Bien bien bien !";
    log4cpp::log_console->errorStream() << "Bien bien bien !";
    log4cpp::log_console->warnStream() << "Bien bien bien !";
    log4cpp::log_console->infoStream() << "Bien bien bien !";
    log4cpp::log_console->debugStream() << "Bien bien bien !";

    return EXIT_SUCCESS;
}
