
#include <cstring>
#include <cmath>
#include "il.h"
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
    
void Image::blit(const Image &img, int x, int y) {
    assert(x>=0);
    assert(y>=0);
    assert(x+img.width < this->width);
    assert(y+img.height < this->height);
    assert(img.channels == this->channels);

    if(img.channels > 0 && img.channels <= 3) {
        for (int j = 0; j < img.height; j++) {
            for (int i = 0; i < img.width; i++) {
                int imgOffset = (j*img.width + i)*img.channels;
                int dstOffset = ((y+j)*img.width + (x+i))*img.channels;
                for (int k = 0; k < img.channels; k++) {
                    this->data[dstOffset+k] = img.data[imgOffset+k];
                }
            }
        }
    }
    else if(img.channels == 4) {
        for (int j = 0; j < img.height; j++) {
            for (int i = 0; i < img.width; i++) {
                int imgOffset = (j*img.width + i)*img.channels;
                int dstOffset = ((y+j)*this->width + (x+i))*this->channels;
                float srcAlpha = static_cast<float>(img.data[imgOffset+3])/255.0f;
                float dstAlpha = static_cast<float>(this->data[dstOffset+3])/255.0f;
                float resAlpha = srcAlpha + dstAlpha*(1.0f-srcAlpha);
                for (int k = 0; k < 3; k++) {
                    float alphaSrcColor = srcAlpha*static_cast<float>(img.data[imgOffset + k]);
                    float alphaDstColor = dstAlpha*static_cast<float>(this->data[dstOffset + k]);
                    this->data[dstOffset+k] = static_cast<unsigned char>((alphaSrcColor + alphaDstColor*(1.0f-srcAlpha))/resAlpha);
                    //this->data[dstOffset+k] = img.data[imgOffset+k];
                }
                unsigned int alpha = floor(resAlpha*256.0f);
                this->data[dstOffset+3] = (alpha >= 0x100 ? 0xff : alpha);
            }
        }
    }
    else {
        log4cpp::log_console->errorStream() << "[Image ]Wrong number of channels !";
        exit(EXIT_FAILURE);
    }
}
