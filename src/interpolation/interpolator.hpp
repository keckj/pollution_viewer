
#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include <cmath>

template <typename T, typename F>
class Interpolator {
    public:
        virtual ~Interpolator() {};
        virtual F* operator()(unsigned int Nx, unsigned int Ny, unsigned int nData, double *x, double *y, T* data) = 0;

    protected:
        Interpolator() {};
};

#endif /* end of include guard: INTERPOLATOR_H */
