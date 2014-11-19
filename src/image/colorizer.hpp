
#ifndef COLORIZER_H
#define COLORIZER_H

#include <ft2build.h> 
#include FT_FREETYPE_H 
#include <type_traits>
#include <cassert>

#include "freetypeUtils.hpp"
#include "colors.hpp"

template <typename F, typename C>
class Colorizer {
    static_assert(std::is_floating_point<F>(), "");
    static_assert(std::is_base_of<Color, C>::value, "");

    public:
        virtual ~Colorizer() {}
        virtual C operator()(const F) const = 0;
    
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

template <typename F, typename C>
void Colorizer<F,C>::generateColorRange() {

    FT_Library library; 
    FT_Face face; 
    
    assert(!FT_Init_FreeType(&library));
    assert(!FT_New_Face( library, "/usr/share/fonts/truetype/freefont/FreeMono.ttf", 0, &face ));

}

#endif /* end of include guard: COLORIZER_H */
