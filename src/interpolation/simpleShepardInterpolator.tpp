
#include "coords.hpp"

template <typename T, typename F>
SimpleShepardInterpolator<T,F>::SimpleShepardInterpolator(double mu) :
    Interpolator<T,F>(),
    mu(mu)
{
}

template <typename T, typename F>
SimpleShepardInterpolator<T,F>::~SimpleShepardInterpolator() {
}


template <typename T, typename F>
F* SimpleShepardInterpolator<T,F>::operator()(unsigned int Nx, unsigned int Ny, unsigned int nData, double *x, double *y, T* data) {

    // valeurs finales évaluées 
    F* density = new F[Nx*Ny];

    // convertir les coordonées [longitude, latitude] => [0,1]^2
    Coords<double> unitCoords = toUnitSquare(Coords<double>(nData, x, y));

    // remplir le tableau de densité en interpolant les données
    for (unsigned int j = 0; j < Ny; j++) {
        F d_y = static_cast<F>(j)/Ny;
        for (unsigned int i = 0; i < Nx; i++) {
            F d_x = static_cast<F>(i)/Nx;
            F d = F(0);
            for (unsigned int k = 0; k < nData; k++) {
                if(data[k] >= T(0)) { //if sampled data exists
                    F w = shepardWeight(k,d_x,d_y,unitCoords,data); 
                    d += w*F(data[k]);
                }
            }
            density[j*Nx+i] = d;
        }
    }

    return density;
}

template <typename T, typename F>
F SimpleShepardInterpolator<T,F>::shepardWeight(unsigned int k, F d_x, F d_y, Coords<double> unitCoords, T* data) {
    F sum = F(0); 
    for (unsigned int j = 0; j < unitCoords.nCoords; j++) {
        if(data[j] >= T(0)) { //if sampled data exists
            double xj = unitCoords.x[j];
            double yj = unitCoords.y[j];
            sum += F(1)/F(std::pow(norm(d_x, d_y, xj, yj), this->mu));
        }
    }
    F xk = unitCoords.x[k];
    F yk = unitCoords.y[k];
    F w = (F(1)/F(std::pow(norm(d_x,d_y,xk,yk), this->mu))) * (F(1)/sum);

    return w;
}

template <typename T, typename F>
F SimpleShepardInterpolator<T,F>::norm(F x1, F y1, F x2, F y2) {
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}
