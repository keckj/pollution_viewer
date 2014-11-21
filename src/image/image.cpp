
#include "image.hpp"

//Template specializations

//Grayscale blit
template <>
void Image<1u>::blit(const Image<1u> &img, unsigned int x, unsigned int y) {
    assert(x+img.width < this->width);
    assert(y+img.height < this->height);

    for (unsigned int j = 0; j < img.height; j++) {
        for (unsigned int i = 0; i < img.width; i++) {
            unsigned int imgOffset = (j*img.width + i)*img.channels;
            unsigned int dstOffset = ((y+j)*img.width + (x+i))*img.channels;
            this->data[dstOffset] = img.data[imgOffset];
        }
    }
}


//RGB blit
template <>
void Image<3u>::blit(const Image<3u> &img, unsigned int x, unsigned int y) {
    assert(x+img.width < this->width);
    assert(y+img.height < this->height);

    for (unsigned int j = 0; j < img.height; j++) {
        for (unsigned int i = 0; i < img.width; i++) {
            unsigned int imgOffset = (j*img.width + i)*img.channels;
            unsigned int dstOffset = ((y+j)*img.width + (x+i))*img.channels;
            this->data[dstOffset] = img.data[imgOffset];
        }
    }
}

//RGBA blit (alpha blit)
template <>
void Image<4u>::blit(const Image<4u> &img, unsigned int x, unsigned int y) {
    for (unsigned int j = 0; j < img.height; j++) {
        for (unsigned int i = 0; i < img.width; i++) {
            unsigned int imgOffset = (j*img.width + i)*img.channels;
            unsigned int dstOffset = ((y+j)*this->width + (x+i))*this->channels;
            float srcAlpha = static_cast<float>(img.data[imgOffset+3])/255.0f;
            float dstAlpha = static_cast<float>(this->data[dstOffset+3])/255.0f;
            float resAlpha = srcAlpha + dstAlpha*(1.0f-srcAlpha);
            for (unsigned int k = 0; k < 3; k++) {
                float alphaSrcColor = srcAlpha*static_cast<float>(img.data[imgOffset + k]);
                float alphaDstColor = dstAlpha*static_cast<float>(this->data[dstOffset + k]);
                this->data[dstOffset+k] = static_cast<unsigned char>((alphaSrcColor + alphaDstColor*(1.0f-srcAlpha))/resAlpha);
            }
            unsigned int alpha = floor(resAlpha*256.0f);
            this->data[dstOffset+3] = (alpha >= 0x100 ? 0xff : alpha);
        }
}
