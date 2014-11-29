
#ifndef LINEARCOLORIZER_H
#define LINEARCOLORIZER_H

#include "colors.hpp"
#include "colorizer.hpp"

template <typename F, unsigned int N>
class LinearColorizer final : public Colorizer<F,N> {
    static_assert(std::is_floating_point<F>(), "");

    public:

    explicit LinearColorizer(InterpolatedData<F> data, Color<N> c1, Color<N> c2) : Colorizer<F,N>(data), c1(c1), c2(c2) {}
    ~LinearColorizer() {}

    virtual Color<N> operator()(const F val) const final {
        F alpha = (val - this->min)/(this->max - this->min);

        Color<N> c1_t = (Color<N>::RGBtoCIE(c1));
        Color<N> c2_t = (Color<N>::RGBtoCIE(c2));
        return Color<N>::linearInterp(alpha, c1, c2);
    }

    private:
    Color<N> c1, c2;


};

#endif /* end of include guard: LINEARCOLORIZER_H */
