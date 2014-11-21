
#include "freetypeUtils.hpp"
#include "stringBlitter.hpp"

StringBlitter::StringBlitter() :
    library(0), face(0)
{
    // initialize library object
    CHECK_FREETYPE_ERROR(FT_Init_FreeType(&library));
}

StringBlitter::~StringBlitter() {
    // destroy library object
    CHECK_FREETYPE_ERROR(FT_Done_FreeType(library));
}

void StringBlitter::loadFontFromFile(const std::string &fontPath, bool logInfo) {
   
    using log4cpp::log_console;
    log4cpp::log_console->infoStream() << "[StringBlitter] Loading font " << fontPath <<"...";

    // release old font if any
    if(face) 
        CHECK_FREETYPE_ERROR(FT_Done_Face(face));

    // load given font
    CHECK_FREETYPE_ERROR(FT_New_Face(library, fontPath.c_str(), 0, &face));

    // print some infos about the font
    if(logInfo)
        freetypeUtils::logFaceInfo(log4cpp::log_console, face);

    // check if font is scalable and has a Unicode charmap
    if(!(face->face_flags & FT_FACE_FLAG_SCALABLE)) {
        log4cpp::log_console->errorStream() << "[StringBlitter] The given font is not scalable !";
        exit(EXIT_FAILURE);
    }
    if(face->charmap == NULL) {
        log4cpp::log_console->errorStream() << "[StringBlitter] The given font does not contain a Unicode charmap !";
        exit(EXIT_FAILURE);
    }
}

void StringBlitter::setPixelSize(unsigned int pixelSize) {
    log4cpp::log_console->debugStream() << "[StringBlitter] Set pixel size to " << pixelSize << ".";
    CHECK_FREETYPE_ERROR(FT_Set_Pixel_Sizes(face,pixelSize,pixelSize));
    //CHECK_FREETYPE_ERROR(FT_Set_Char_Size(face, 0,16*64,300,300));
}

StringImageInfo StringBlitter::evaluateTextImageSize(const std::string &str) {
    FT_UInt index;
    FT_GlyphSlot slot = face->glyph;
    const FT_Bitmap &bitmap = face->glyph->bitmap;

    unsigned int imgWidth = 0, imgHeight = 0;
    unsigned int maxBearingY = 0;

    for (unsigned int i = 0; i < str.size(); i++) {
        // retrieve glyph index
        index = FT_Get_Char_Index(face, static_cast<unsigned char>(str[i])); 
        
        // load glyph image into the slot (erase previous one)
        CHECK_FREETYPE_ERROR(FT_Load_Glyph(face, index, FT_LOAD_DEFAULT));

        // convert glyph to an anti-aliased bitmap
        CHECK_FREETYPE_ERROR(FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL));

        imgWidth += slot->advance.x >> 6;
        imgHeight = std::max(imgHeight, static_cast<unsigned int>(slot->bitmap_top + bitmap.rows));
        maxBearingY = std::max(maxBearingY, static_cast<unsigned int>(slot->bitmap_top));
    }
    
    log4cpp::log_console->debugStream() << "[FreeType] Image Size (in pixels): " << imgWidth << "x" << imgHeight;
    log4cpp::log_console->debugStream() << "[FreeType] Max Y-axis bearing (in pixels): " << maxBearingY;

    return StringImageInfo(imgWidth, imgHeight, maxBearingY);
}

Image StringBlitter::generateTextImageGraylevel(const std::string &str) {
    FT_UInt index;
    FT_GlyphSlot slot = face->glyph;
    const FT_Bitmap &bitmap = face->glyph->bitmap;

    const StringImageInfo imgInfo = evaluateTextImageSize(str);

    Image image(imgInfo.imgWidth, imgInfo.imgHeight, 1u);
    unsigned int x = 0;
    
    for (unsigned int i = 0; i < str.size(); i++) {
        index = FT_Get_Char_Index(face, static_cast<unsigned char>(str[i])); 
        CHECK_FREETYPE_ERROR(FT_Load_Glyph(face, index, FT_LOAD_DEFAULT));
        CHECK_FREETYPE_ERROR(FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL));
        blitCharacter(image, 
                x+static_cast<unsigned int>(slot->bitmap_left), 
                static_cast<unsigned int>(static_cast<int>(imgInfo.maxBearingY) - slot->bitmap_top),
                bitmap);
        x += slot->advance.x >> 6;
    }

    return image;
}

Image StringBlitter::generateTextImageRGBA(const std::string &str, const ColorRGBA &color) {
    
    const int channels = 4;
    Image grayscaleImg = generateTextImageGraylevel(str);
    Image rgbaImg(grayscaleImg.width, grayscaleImg.height, channels);
    
    const unsigned char *colorData = reinterpret_cast<const unsigned char *>(&color);

    for (unsigned int j = 0; j < rgbaImg.height; j++) {
        for (unsigned int i = 0; i < rgbaImg.width; i++) {
            for (unsigned int k = 0; k < channels; k++) {
                float color = static_cast<float>(colorData[k])*grayscaleImg.data[j*grayscaleImg.width+i]/255.0f;
                rgbaImg.data[(j*rgbaImg.width+i)*channels+k] = static_cast<unsigned char>(color);
            }
        }
    }
    
    grayscaleImg.freeData();
    return rgbaImg;
}
        
void StringBlitter::blitCharacter(const Image &image, unsigned int x, unsigned int y, const FT_Bitmap &bitmap) {
    // check if bitmap has 256 gray levels
    assert(bitmap.pixel_mode == FT_PIXEL_MODE_GRAY);
    assert(bitmap.num_grays  == 0x100);

    // check if image has only one channel
    assert(image.channels == 1);

    unsigned char *glyphData = bitmap.buffer;
    
    for (unsigned int j = 0; j < static_cast<unsigned int>(bitmap.rows); j++) {
        for (unsigned int i = 0; i < static_cast<unsigned int>(bitmap.width); i++) {
            image.data[(y+j)*image.width+(x+i)] = glyphData[j*static_cast<unsigned int>(bitmap.pitch) +i];
        }
    }
}
