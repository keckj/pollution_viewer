
#include "freetypeUtils.hpp"

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

// Face flags /////////////////////////////////////////////////
        static const unsigned int faceFlagsCount = 15;
        static const char* faceFlagStrings[faceFlagsCount] = { 
            "SCALABLE", 
            "FIXED_SIZES", 
            "FIXED_WIDTH", 
            "SFNT", 
            "HORIZONTAL", 
            "VERTICAL", 
            "KERNING", 
            "FAST_GLYPHS", 
            "MULTIPLE_MASTERS", 
            "GLYPH_NAMES", 
            "EXTERNAL_STREAM", 
            "HINTER", 
            "CID_KEYED", 
            "TRICKY", 
            "COLOR"
        };
///////////////////////////////////////////////////////////////

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
    
    void logFaceInfo(log4cpp::Category *log, const FT_Face &face) {
        std::stringstream size, flags;
        for (unsigned int i = 0; i < faceFlagsCount; i++) {
            if(face->face_flags & (1l << i))
                flags << faceFlagStrings[i] << " ";
        }
        
        for (int i = 0; i < face->num_fixed_sizes; i++) {
            FT_Bitmap_Size bsize = face->available_sizes[i];
            size << bsize.size << ", ";
        }

        log->infoStream() << "[FreeType] Face " << face->family_name << "." << face->style_name << " infomations";
        log->infoStream() << "[FreeType] \tNum Glyphs: " << face->num_glyphs;
        log->infoStream() << "[FreeType] \tUnit per EM: " << face->units_per_EM;
        log->infoStream() << "[FreeType] \tEmbedded Bitmap Strikes: " << face->num_fixed_sizes;
        if(face->num_fixed_sizes > 0)
            log->infoStream() << "\t[FreeType] Bitmap Strikes Sizes: " << size.str();
        log->infoStream() << "[FreeType] \tFlags: " << flags.str();
    }

}
