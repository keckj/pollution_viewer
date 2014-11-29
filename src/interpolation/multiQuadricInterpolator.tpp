#include <Eigen/IterativeLinearSolvers>

#include "coords.hpp"

template <typename T, typename F>
MultiQuadricInterpolator<T,F>::MultiQuadricInterpolator(double delta_min, double delta_max) :
    Interpolator<T,F>(),
    delta_min(delta_min),
    delta_max(delta_max)
{
}

template <typename T, typename F>
MultiQuadricInterpolator<T,F>::~MultiQuadricInterpolator() {
}


template <typename T, typename F>
InterpolatedData<F> MultiQuadricInterpolator<T,F>::operator()(unsigned int Nx, unsigned int Ny, unsigned int nData, double *x, double *y, T* data) {

    // valeurs finales évaluées 
    F* density = new F[Nx*Ny];
    F max = std::numeric_limits<F>::min();
    F min = std::numeric_limits<F>::max();

    // convertir les coordonées [longitude, latitude] => [0,1]^2
    Coords<double> unitCoords = toUnitSquare(Coords<double>(nData, x, y));


    // remplir le tableau de densité en interpolant les données
    // some sample data do not exists, we first need to check how many
    unsigned int n = nData;
    for (int i = 0; i < nData; ++i)
    {
        if (data[i] < T(0))
        {
            n--;
        }
    }
    Eigen::MatrixXf M(n,n);

    // filling matrix
    for (unsigned int j = 0; j < nData; j++) {
        for (unsigned int i = 0; i < nData; i++){
            if(data[k] >= T(0)) { //if sampled data exists
                F w = hardyQuadric(i,unitCoords.x[j],unitCoords.y[j],unitCoords,n);
                M[i,j] = static_cast<float>(w);
            }
        }
    }
    // solve sysem

    return InterpolatedData<F>(density, min, max, Nx, Ny);
}
template <typename T, typename F>
F MultiQuadricInterpolator<T,F>::hardyQuadric(unsigned int k, F d_x, F d_y, Coords<double> unitCoords, unsigned int n) {

    double delta_i = this->delta_min * std::pow((this->delta_max/this->delta_min),static_cast<F>(k-1)/(n-1));
    F x_k = unitCoords.x[k];
    F y_k = unitCoords.y[k];

    F n_x = norm(d_x,x_k);
    F n_y = norm(d_y,y_k);

    return sqrt(n_x*n_x + n_y*n_y + delta_i);


}

template <typename T, typename F>
F MultiQuadricInterpolator<T,F>::norm(F x1, F x2) {
    return sqrt((x2-x1)*(x2-x1));
}
