
#ifndef COLORIZER_H
#define COLORIZER_H

#include <type_traits>
#include <cassert>
#include <algorithm>
#include <iomanip>   

#include "stringBlitter.hpp"
#include "colors.hpp"
#include "image.hpp"

template <typename F, unsigned int N>
class Colorizer {
    static_assert(std::is_floating_point<F>(), "");

    public:
        virtual ~Colorizer() {}
        virtual Color<N> operator()(const F) const = 0;
    
        void generateColorRange();

    protected:
        explicit Colorizer(F min, F max) : min(min), max(max) {};
        explicit Colorizer(unsigned int nData, F* data) : 
            min(data[0]),
            max(data[0])
        {
            for (unsigned int i = 1; i < nData; i++) {
                    this->min = (data[i] < this->min ? data[i] : this->min);
                    this->max = (data[i] > this->max ? data[i] : this->max);
            }
        };

        F min;
        F max;
};

template <typename F, unsigned int N>
void Colorizer<F,N>::generateColorRange() {
    
    using log4cpp::log_console;
    log_console->infoStream() << "[Colorizer] Generating color overlay...";
    
    const std::string fontPath = "fonts/FreeMonoBold.ttf";
    StringBlitter blitter;
    blitter.loadFontFromFile(fontPath);

       
    RGBAImageInitializer overlayInit = [&] (unsigned int i, unsigned int j, unsigned int width, unsigned int height) -> Color<N> {
        const unsigned int borderSize = 6u;

        if(i < borderSize || j < borderSize || i+borderSize >= height || j+borderSize >= width)
            return ColorRGBA::blue;
        else 
            return ColorRGBA::white;
    };

    RGBAImageInitializer colorRangeInit = [&] (unsigned int i, unsigned int j, unsigned int width, unsigned int height) -> Color<N> {
        F fy = static_cast<F>(i)/height; 

        const unsigned int borderSize = 3u;
        if(i < borderSize || j < borderSize || i+borderSize >= height || j+borderSize >= width)
            return ColorRGBA::black;

        const F val = min + (F(1)-fy)*(max - min);
        return this->operator()(val);
    };

    Image<4u> overlay(600u,1200u, overlayInit);
    Image<4u> colorRange(400u,1000u, colorRangeInit);
    Image<4u> text;
    
    overlay.blit(colorRange, 40u, 150u);

    blitter.setPixelSize(40u);
    std::stringstream ss;
    StringImageInfo info = blitter.evaluateTextImageSize(ss.str());
    text = blitter.generateTextImageRGBA("Particules PM10 (µg/m³)", ColorRGBA::blue);
    overlay.blit(text, 30, 30 - info.imgHeight/3);         
    text.freeData();
  
    blitter.setPixelSize(50u);
    unsigned int nLevels = 5;
    for (unsigned int i = 0; i < nLevels; i++) {
        ss.seekp(std::ios_base::beg);
        F alpha = static_cast<F>(i)/(nLevels-1);
        F val = min + (F(1) - alpha)*(max - min);
        ss << std::setprecision(3) << val;
            
        info = blitter.evaluateTextImageSize(ss.str());
        text = blitter.generateTextImageRGBA(ss.str(), ColorRGBA::blue);
        
        overlay.blit(text, 450u, 150+i*1000/(nLevels-1)- info.imgHeight/3);         

        text.freeData();
    }

    overlay.save("img/", "overlay", "png");
}

#endif /* end of include guard: COLORIZER_H */
