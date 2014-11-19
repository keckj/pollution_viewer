
#include "freetypeUtils.hpp"

namespace freetypeUtils {

    std::string toStringError(FT_Error error) {
        return errorStrings[int(error)];
    };

    void freeTypeAssert(FT_Error error, const std::string &file, unsigned int line) {
        if(error != 0x00) {
            log4cpp::log_console->errorStream() << "[FreetypeLibrary] Error in file " << file << " at line " << line << ".";
            log4cpp::log_console->errorStream() << "[FreetypeLibrary] Message: " << toStringError(error); 
            exit(EXIT_FAILURE);
        }
    }

}
