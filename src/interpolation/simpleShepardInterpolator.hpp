
#ifndef SIMPLESHEPARDINTERPOLATOR_H
#define SIMPLESHEPARDINTERPOLATOR_H

#include "interpolator.hpp"
#include "coords.hpp"

template <typename T, typename F>
class SimpleShepardInterpolator : public Interpolator<T,F> {
    
    public:
        SimpleShepardInterpolator(double mu); 
        ~SimpleShepardInterpolator();

        F* operator()(unsigned int Nx, unsigned int Ny, unsigned int nData, double *x, double *y, T* data);

    private:
        double mu;
                
        F shepardWeight(unsigned int k, F d_x, F d_y, Coords<double> unitCoords, T* data);
        F norm(F x1, F y1, F x2, F y2);
};

#include "simpleShepardInterpolator.tpp"

#endif /* end of include guard: SIMPLESHEPARDSIMPLESHEPARDINTERPOLATOR_H */

