
#ifndef COLORIZER_H
#define COLORIZER_H

#include <type_traits>
#include "colors.hpp"

template <typename F, typename C>
class Colorizer {
    static_assert(std::is_floating_point<F>(), "");
    static_assert(std::is_base_of<Color, C>::value, "");

    public:
        virtual ~Colorizer() {}
        virtual C operator()(const F) const = 0;
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

#endif /* end of include guard: COLORIZER_H */
