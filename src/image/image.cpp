
#include "il.h"
#include <cstring>
#include "ilu.h"

#include "image.hpp"
#include "log.hpp"

Image::Image(): width(0), height(0), channels(0), data(0) {};
Image::Image(int width, int height, int channels, unsigned char initialValue): 
    width(width), height(height), channels(channels), data(0) 
{
    data = new unsigned char[width*height*channels];
    memset(data, initialValue, static_cast<unsigned int>(width*height*channels)*sizeof(unsigned char));
};

Image::~Image() {
}

void Image::freeData() {
    delete [] data;
}

void Image::save(const std::string &imgFolder, const std::string &imgName, const std::string &imgExt, bool flip) {

    using log4cpp::log_console;
    
    std::string filePath = imgFolder+imgName+std::string(".")+imgExt;

    // Get image format from number of channels
    ILenum imageFormat;
    switch(channels) {
        case 1:
            imageFormat = IL_LUMINANCE;
            break;
        case 3:
            imageFormat = IL_RGB;
            break;
        case 4:
            imageFormat = IL_RGBA;
            break;
        default:
            log_console->errorStream() << "Image format with " << channels << " channels are not supported yet !";
            exit(EXIT_FAILURE);
    }

    // Get image type from fileExt name
    ILenum imageType;
    if(imgExt.compare("png") == 0)
        imageType = IL_PNG;
    else if(imgExt.compare("jpg") == 0)
        imageType = IL_JPG;
    else if(imgExt.compare("raw") == 0)
        imageType = IL_RAW;
    else {
        log_console->errorStream() << "Image extension " << imgExt << " is not supported yet !";
        exit(EXIT_FAILURE);
    }

    ILuint imageId = ilGenImage();
    ilBindImage(imageId);
    ilTexImage(static_cast<unsigned int>(width), static_cast<unsigned int>(height),
            0u, static_cast<unsigned int>(channels)*sizeof(unsigned char), imageFormat, IL_UNSIGNED_BYTE, data);
    if(!flip)
        iluFlipImage();
    ilEnable(IL_FILE_OVERWRITE);
    ilSave(imageType, filePath.c_str());
    ilBindImage(0);
    ilDeleteImages(1, &imageId);
}
