
#ifndef IMAGE_H
#define IMAGE_H

#include <functional>
#include <string>

#include "colors.hpp"

struct StringImageInfo {
    unsigned int imgWidth;
    unsigned int imgHeight;
    unsigned int maxBearingY;
    StringImageInfo(): imgWidth(0u), imgHeight(0u), maxBearingY(0u) {};
    explicit StringImageInfo(unsigned int imgWidth, unsigned int imgHeight, unsigned int maxBearingY):
        imgWidth(imgWidth), imgHeight(imgHeight), maxBearingY(maxBearingY) {};
};


using RGBA_Initializer = std::function<ColorRGBA(unsigned int, unsigned int)>;
using RGB_Initializer = std::function<ColorRGB(unsigned int, unsigned int)>;
using Grayscale_Initializer = std::function<ColorMonochrome(unsigned int, unsigned int)>;

//Image convention: 1st pixel = TOP-LEFT CORNER
struct Image {
    unsigned int width;
    unsigned int height;
    unsigned int channels;
    unsigned char *data;

    Image();
    explicit Image(unsigned int width, unsigned int height, unsigned int channels, unsigned char initialValue = 0); 
    //explicit Image(unsigned int width, unsigned int height, std::function<ColorRGBA(unsigned int, unsigned int)> initRGBA);
    ~Image();

    //blit image img to current image from origin (x,y) (ORIGIN = TOP-LEFT-CORNER)
    void blit(const Image &img, unsigned int x, unsigned int y);
    void save(const std::string &imgFolder, const std::string &imgName, const std::string &imgExt, bool flip=false);
    void freeData();
};

#endif /* end of include guard: IMAGE_H */
