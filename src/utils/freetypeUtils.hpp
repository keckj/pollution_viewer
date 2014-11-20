
#ifndef FREETYPEUTILS_HH
#define FREETYPEUTILS_HH

#include <string>
#include <ft2build.h> 
#include FT_FREETYPE_H 

#include "log.hpp"

namespace freetypeUtils {


    std::string toStringError(FT_Error error);
    void freeTypeAssert(FT_Error error, const std::string &file, unsigned int line);
    void logFaceInfo(log4cpp::Category *log, const FT_Face &face);
}

//Error checking macro
#define CHECK_FREETYPE_ERROR(error) do { freetypeUtils::freeTypeAssert(error, __FILE__, __LINE__); } while(0)

#endif /* end of include guard: FREETYPEUTILS_HH */



