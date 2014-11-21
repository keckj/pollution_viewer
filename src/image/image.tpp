
#include <cstring>
#include <cmath>
#include "il.h"
#include "ilu.h"

#include "image.hpp"
#include "log.hpp"

template <unsigned int N>
unsigned int Image<N>::channels = N;

template <unsigned int N>
Image<N>::Image(unsigned int width, unsigned int height, unsigned int channels, unsigned char initialValue): 
    width(width), height(height), data(0) 
{
    data = new unsigned char[width*height*channels];
    memset(data, initialValue, width*height*channels*sizeof(unsigned char));
};

template <unsigned int N>
Image<N>::Image(unsigned int width, unsigned int height, const ImageInitializer<N> &I) :
    width(width), height(height)
{
    data = new unsigned char[width*height*channels];
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            const Color<N> &color = I(i,j,width,height);
            unsigned int offset = (i*width+j)*channels;
            for (unsigned int k = 0; k < channels; k++) {
                data[offset+k] = color[k];
            }
        }
    }
}


template <unsigned int N>
Image<N>::~Image() {
}

template <unsigned int N>
void Image<N>::freeData() {
    delete [] data;
}

template <unsigned int N>
void Image<N>::save(const std::string &imgFolder, const std::string &imgName, const std::string &imgExt, bool flip) {
    static_assert(N==1 || N==3 || N==4, "The number of image channels must be 1,3 or 4 !");

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
    ilTexImage(width, height, 0u, channels*sizeof(unsigned char), imageFormat, IL_UNSIGNED_BYTE, data);
    if(!flip)
        iluFlipImage();
    ilEnable(IL_FILE_OVERWRITE);
    ilSave(imageType, filePath.c_str());
    ilBindImage(0);
    ilDeleteImages(1, &imageId);
}

//Specialized in image.cpp
template <unsigned int N>
void Image<N>::blit(const Image<N> &img, unsigned int x, unsigned int y) {
    log4cpp::log_console->errorStream() << "[Image] Wrong number of channels (blit not supported yet) !";
    exit(EXIT_FAILURE);
}


