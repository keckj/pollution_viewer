
#ifndef MULTIQUADRICINTERPOLATOR_H
#define MULTIQUADRICINTERPOLATOR_H

#include "interpolator.hpp"
#include "coords.hpp"

template <typename T, typename F>
class MultiQuadricInterpolator : public Interpolator<T,F> {
    
    public:
        MultiQuadricInterpolator(double delta_min, double delta_max); 
        ~MultiQuadricInterpolator();

        InterpolatedData<F> operator()(unsigned int Nx, unsigned int Ny, unsigned int nData, double *x, double *y, T* data) const;

    private:
        double delta_min;
        double delta_max;
                
        F hardyQuadric(unsigned int k, F d_x, F d_y, Coords<double> unitCoords,unsigned int nData) const;
        F norm(F x1, F x2) const;
};

#include "multiQuadricInterpolator.tpp"

#endif /* end of include guard: MULTIQUADRICINTERPOLATOR_H */

