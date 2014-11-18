
#ifndef LINEARCOLORIZER_H
#define LINEARCOLORIZER_H

#include "colors.hpp"
#include "colorizer.hpp"

template <typename F, typename C>
class LinearColorizer final : public Colorizer<F,C> {
    static_assert(std::is_floating_point<F>(), "");
    static_assert(std::is_base_of<Color, C>::value, "");

    public:

    explicit LinearColorizer(F minValue, F maxValue, C c1, C c2) : Colorizer<F,C>(minValue,maxValue), c1(c1), c2(c2) {}
    explicit LinearColorizer(unsigned int nData, F *targetData, C c1, C c2) : Colorizer<F,C>(nData, targetData), c1(c1), c2(c2) {}
    ~LinearColorizer() {}

    virtual C operator()(const F val) const final {
        F alpha = (val - this->min)/(this->max - this->min);
        return C::linearInterp(alpha, c1, c2);
    }

    private:
    C c1, c2;


};

#endif /* end of include guard: LINEARCOLORIZER_H */
