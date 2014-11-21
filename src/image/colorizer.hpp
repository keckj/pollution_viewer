
#ifndef COLORIZER_H
#define COLORIZER_H

#include <type_traits>
#include <cassert>
#include <algorithm>

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
       
    //const std::string fontPath = "fonts/FreeMono.ttf";
    //StringBlitter blitter;
    //blitter.loadFontFromFile(fontPath);
    //blitter.setPixelSize(16u);
    //Image img = blitter.generateTextImageRGBA("lololo", ColorRGBA(255,0,0,255));
        
    const unsigned int borderPixels = 5u;

    RGBAImageInitializer overlayInit = [&] (unsigned int i, unsigned int j, unsigned int width, unsigned int height) -> Color<N> {
        float fx = static_cast<float>(j)/width; 
        float fy = static_cast<float>(i)/height; 

        if(i < borderPixels || j < borderPixels || i+borderPixels >= height || j+borderPixels >= width)
            return ColorRGBA::blue;
        else 
            return ColorRGBA::white;
    };

    Image overlay(800u,600u, overlayInit);
    overlay.save("img", "gen", "png");
}

#endif /* end of include guard: COLORIZER_H */
