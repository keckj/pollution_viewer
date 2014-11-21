
#ifndef LINEARCOLORIZER_H
#define LINEARCOLORIZER_H

#include "colors.hpp"
#include "colorizer.hpp"

template <typename F, unsigned int N>
class LinearColorizer final : public Colorizer<F,N> {
    static_assert(std::is_floating_point<F>(), "");

    public:

    explicit LinearColorizer(F minValue, F maxValue, Color<N> c1, Color<N> c2) : Colorizer<F,N>(minValue,maxValue), c1(c1), c2(c2) {}
    explicit LinearColorizer(unsigned int nData, F *targetData, Color<N> c1, Color<N> c2) : Colorizer<F,N>(nData, targetData), c1(c1), c2(c2) {}
    ~LinearColorizer() {}

    virtual Color<N> operator()(const F val) const final {
        F alpha = (val - this->min)/(this->max - this->min);
        return Color<N>::linearInterp(alpha, c1, c2);
    }

    private:
    Color<N> c1, c2;


};

#endif /* end of include guard: LINEARCOLORIZER_H */
