
#ifndef IMAGE_H
#define IMAGE_H

#include <string>

struct StringImageInfo {
    int imgWidth;
    int imgHeight;
    int maxBearingY;
    StringImageInfo(): imgWidth(0), imgHeight(0), maxBearingY(0) {};
    StringImageInfo(int imgWidth, int imgHeight, int maxBearingY):
        imgWidth(imgWidth), imgHeight(imgHeight), maxBearingY(maxBearingY) {};
};

struct Image {
    int width;
    int height;
    int channels;
    unsigned char *data;

    Image();
    Image(int width, int height, int channels, unsigned char initialValue = 0);
    ~Image();

    void save(const std::string &imgFolder, const std::string &imgName, const std::string &imgExt, bool flip=false);
    void freeData();
};

#endif /* end of include guard: IMAGE_H */
