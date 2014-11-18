
#ifndef IMAGEGENERATOR_H
#define IMAGEGENERATOR_H

#include "log.hpp"

class ImageGenerator {
   
    public:
    template <typename F, typename C>
    static void generateImage(unsigned int imgWidth, unsigned int imgHeight, F* data, 
            const Colorizer<F,C> &colorizer,
            const std::string &dstFolder, const std::string &fileName, const std::string &fileExt) {

        using log4cpp::log_console;

        // Convert interpolated data to colors with the given colorizer
        const unsigned int channels = C::getChannelCount();
        unsigned char *imageData = new unsigned char[imgWidth*imgHeight*channels];

        for (unsigned int j = 0; j < imgHeight; j++) {
            for (unsigned int i = 0; i < imgWidth; i++) {
                C interpolatedColor = colorizer(data[j*imgWidth+i]);
                unsigned char *colorData = reinterpret_cast<unsigned char*>(&interpolatedColor); //little pointer hack
                for(unsigned int k = 0; k < channels; k++) {
                        imageData[(j*imgWidth+i)*channels+k] = colorData[k];
                }
            }
        }

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
        if(fileExt.compare("png") == 0)
            imageType = IL_PNG;
        else if(fileExt.compare("jpg") == 0)
            imageType = IL_JPG;
        else if(fileExt.compare("raw") == 0)
            imageType = IL_RAW;
        else {
                log_console->errorStream() << "Image extension " << fileExt << " is not supported yet !";
                exit(EXIT_FAILURE);
        }
        
        // Generate and bind image (OpenGL style)
        ILuint imageId = ilGenImage();
        ilBindImage(imageId);

        // Write image to RAM
        ilTexImage(imgWidth, imgHeight, 1u,
                channels*sizeof(unsigned char), imageFormat, IL_UNSIGNED_BYTE,
                imageData);

        // Write image to the disk
        std::string filePath(dstFolder+fileName+"."+fileExt);
        ilEnable(IL_FILE_OVERWRITE);
        ilSave(imageType, filePath.c_str());
        
        // Clean up
        ilBindImage(0);
        ilDeleteImages(1, &imageId);
        delete [] imageData;
    }
};

#endif /* end of include guard: IMAGEGENERATOR_H */
