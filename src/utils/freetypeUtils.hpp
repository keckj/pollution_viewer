
#ifndef FREETYPEUTILS_HH
#define FREETYPEUTILS_HH

#include <string>
#include <ft2build.h> 
#include FT_FREETYPE_H 

#include "log.hpp"

namespace freetypeUtils {

// Error String array generation
// This is well explained in the error header of the library 
// Need to see more libs like this
#undef __FTERRORS_H__                                           
#define FT_ERRORDEF( e, v, s )  s,                       
#define FT_ERROR_START_LIST     {                               
#define FT_ERROR_END_LIST       0};                     

    static const char* errorStrings[] = 
#include FT_ERRORS_H                                            
//////////////////////////////////////////////////////////////

    std::string toStringError(FT_Error error);
    void freeTypeAssert(FT_Error error, const std::string &file, unsigned int line);
}

//Error checking macro
#define CHECK_FREETYPE_ERROR(error) do { freetypeUtils::freeTypeAssert(error, __FILE__, __LINE__); } while(0)

#endif /* end of include guard: FREETYPEUTILS_HH */



