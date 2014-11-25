
#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include <cmath>

template <typename F>
struct InterpolatedData {
    F* density;
    F min;
    F max;
    unsigned int gridWidth;
    unsigned int gridHeight;
    
    InterpolatedData(): density(0), min(0), max(0), gridWidth(0), gridHeight(0) {
    }

    InterpolatedData(F* density, F min, F max, unsigned int gridWidth, unsigned int gridHeight):
        density(density), min(min), max(max), gridWidth(gridWidth), gridHeight(gridHeight) {
    }
};

template <typename T, typename F>
class Interpolator {
    public:
        virtual ~Interpolator() {};
        virtual InterpolatedData<F> operator()(unsigned int Nx, unsigned int Ny, unsigned int nData, double *x, double *y, T* data) const = 0;

    protected:
        Interpolator() {};
};

#endif /* end of include guard: INTERPOLATOR_H */
