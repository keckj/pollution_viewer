
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
template <unsigned int N>
struct Image {
    unsigned int width;
    unsigned int height;
    unsigned char *data;
    
    Image();
    explicit Image(unsigned int width, unsigned int height, unsigned char initialValue = 0); 
    explicit Image(unsigned int width, unsigned int height, const ImageInitializer<N> &I); 
   
    ~Image();

    //blit image img to current image from origin (x,y) (ORIGIN = TOP-LEFT-CORNER)
    void blit(const Image<N> &img, unsigned int x, unsigned int y);
    void save(const std::string &imgFolder, const std::string &imgName, const std::string &imgExt, bool flip=false);
    void freeData();

    static unsigned int channels;
};

using ImageRGBA = Image<4u>;
using ImageRGB = Image<3u>;
using ImageGraylevel = Image<1u>;

#include "image.tpp"

#endif /* end of include guard: IMAGE_H */
