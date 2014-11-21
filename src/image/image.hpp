
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

//Image initializers///////////////////////////////////////////////////
//Matrix like images (i,j) -> (0,0) = top left corner
template <unsigned int N>
using ImageInitializer = std::function<Color<N>(unsigned int, unsigned int, unsigned int, unsigned int)>;
//                              args:                i            j          imgWidth      imgHeight

using GrayscaleImageInitializer = ImageInitializer<1u>;
using RGBImageInitializer = ImageInitializer<3u>;
using RGBAImageInitializer = ImageInitializer<4u>;
//////////////////////////////////////////////////////////////////////

//Image convention: 1st pixel = TOP-LEFT CORNER
struct Image {
    unsigned int width;
    unsigned int height;
    unsigned int channels;
    unsigned char *data;

    Image();
    explicit Image(unsigned int width, unsigned int height, unsigned int channels, unsigned char initialValue = 0); 

    template <unsigned int N>
    explicit Image(unsigned int width, unsigned int height, const ImageInitializer<N> &I); 

    ~Image();

    //blit image img to current image from origin (x,y) (ORIGIN = TOP-LEFT-CORNER)
    void blit(const Image &img, unsigned int x, unsigned int y);
    void save(const std::string &imgFolder, const std::string &imgName, const std::string &imgExt, bool flip=false);
    void freeData();
};
    

template <unsigned int N>
Image::Image(unsigned int width, unsigned int height, const ImageInitializer<N> &I) :
    width(width), height(height), channels(Color<N>::channels)
{
    data = new unsigned char[width*height*channels];
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            const Color<N> &color = I(i,j,width,height);
            const unsigned char *colorData = reinterpret_cast<const unsigned char*>(&color);
            unsigned int offset = (i*width+j)*channels;
            for (unsigned int k = 0; k < channels; k++) {
                data[offset+k] = colorData[k];
            }
        }
    }
}

#endif /* end of include guard: IMAGE_H */
