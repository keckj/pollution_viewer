
#ifndef STRINGBLITTER_H
#define STRINGBLITTER_H

#include <ft2build.h> 
#include FT_FREETYPE_H 
#include <string>

#include "colors.hpp"
#include "image.hpp"

class StringBlitter {
    
    public:
        StringBlitter();
        ~StringBlitter();

        void loadFontFromFile(const std::string &fontPath, bool logInfo = true);
        void setPixelSize(unsigned int pixelSize);
    
        //Image convention: 1st pixel = TOP-LEFT CORNER
        StringImageInfo evaluateTextImageSize(const std::string &str);
        Image generateTextImageGraylevel(const std::string &str);
        Image generateTextImageRGBA(const std::string &str, const ColorRGBA &color);

    private:
        FT_Library library; 
        FT_Face face; 
        
        void blitCharacter(const Image &image, unsigned int x, unsigned int y, const FT_Bitmap &bitmap);
};

#endif /* end of include guard: STRINGBLITTER_H */
