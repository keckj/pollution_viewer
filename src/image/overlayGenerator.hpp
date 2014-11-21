
#ifndef OVERLAYGENERATOR_H
#define OVERLAYGENERATOR_H

#include "il.h"
#include "ilu.h"

#include "log.hpp"
#include "image.hpp"

class OverlayGenerator {
   
    public:
    template <typename F, typename C>
    static void generateImage(unsigned int imgWidth, unsigned int imgHeight, F* data, 
            const Colorizer<F,C> &colorizer,
            const std::string &dstFolder, const std::string &fileName, const std::string &fileExt) {

        using log4cpp::log_console;

        // Convert interpolated data to colors with the given colorizer
        const unsigned int channels = C::getChannelCount();
        Image img(imgWidth, imgHeight, channels);

        for (unsigned int j = 0; j < imgHeight; j++) {
            for (unsigned int i = 0; i < imgWidth; i++) {
                C interpolatedColor = colorizer(data[j*imgWidth+i]);
                unsigned char *colorData = reinterpret_cast<unsigned char*>(&interpolatedColor); //little pointer hack
                for(unsigned int k = 0; k < channels; k++) {
                        img.data[(j*imgWidth+i)*channels+k] = colorData[k];
                }
            }
        }

        //save overlay, flipped because it is a texture
        img.save(dstFolder, fileName, fileExt, true);
        
        img.freeData();
    }
};

#endif /* end of include guard: OVERLAYGENERATOR_H */
