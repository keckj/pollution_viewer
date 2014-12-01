#include <Eigen/Dense>
// #include <Eigen/Sparse>
// #include <Eigen/SparseQR>
// #include <Eigen/Core>
#include <vector>

#include "coords.hpp"

using namespace std;
using namespace Eigen;

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
InterpolatedData<F> MultiQuadricInterpolator<T,F>::operator()(unsigned int Nx, unsigned int Ny,
 unsigned int nData, double *x, double *y, T* data) const{

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
    // SparseMatrix<double> M;
    MatrixXd A = MatrixXd::Random(n,n);
    MatrixXd b = MatrixXd::Random(n,1);

    // filling matrix
    unsigned int i_safe = 0;
    unsigned int j_safe = 0;
    for (unsigned int i = 0; i < nData; i++){
        if (data[i] >= T(0)){
            b(i_safe,0) = double(data[i]);
            i_safe ++;
        } 
    }
    i_safe = 0;
    j_safe = 0;
    for (unsigned int j = 0; j < nData; j++){
        if (data[j] >= T(0)){
            i_safe = 0; 
            for (unsigned int i = 0; i < nData; i++){
                if (data[i] >= T(0)){
                    F w = hardyQuadric(i_safe,unitCoords.x[j],unitCoords.y[j],i,unitCoords,n);
                    A(i_safe,j_safe) = w;
                    i_safe ++;
                }
            }
            j_safe ++;
        }
    }




    // solve sysem
    MatrixXd xQR = A.colPivHouseholderQr().solve(b);
    // cout << b << endl;   
    // cout << "Here is the (unique) solution xQR to the equation AxQR=B:\n" << xQR << endl;
    // cout << "Relative error: " << (A*xQR-b).norm() / b.norm() << endl;

    unsigned int k_safe = 0;
    // remplir le tableau de densité en interpolant les données
    for (unsigned int j = 0; j < Ny; j++) {
        F d_y = static_cast<F>(j)/Ny;
        for (unsigned int i = 0; i < Nx; i++) {
            F d_x = static_cast<F>(i)/Nx;
            F d = F(0);
            k_safe = 0;
            for (unsigned int k = 0; k < nData; k++) {
                if(data[k] >= T(0)) { //if sampled data exists
                    F w = hardyQuadric(k_safe,d_x,d_y,k,unitCoords,n);
                    d += F(xQR(k_safe,0)) * w;
                    k_safe ++;
                }
            }
            max = (d > max) ? d : max;
            min = (d < min) ? d : min;
            density[j*Nx+i] = d;
        }
    }

    return InterpolatedData<F>(density, min, max, Nx, Ny);
}
template <typename T, typename F>
F MultiQuadricInterpolator<T,F>::hardyQuadric(unsigned int k, F d_x, F d_y, unsigned int kreal,Coords<double> unitCoords, unsigned int n) const{

    double delta_i = this->delta_min * std::pow((this->delta_max/this->delta_min),double(k-1)/double(n-1));
    if (k==0){
        delta_i = this->delta_min * std::pow((this->delta_min/this->delta_max),1.0/double(n-1));
    }
    if (k == n){
        delta_i = this->delta_min;
    }



    F x_k = unitCoords.x[kreal];
    F y_k = unitCoords.y[kreal];
    F n_x = norm(d_x,x_k);
    F n_y = norm(d_y,y_k);

    // cout << "shepard" << endl;
    // cout << this->delta_min << "," << this->delta_max << endl;
    // cout << k << "," << n << endl;
    // cout << delta_i << endl;
    // cout << d_x << "," << d_y << endl;
    // cout << x_k << "," << y_k << endl;
    // cout << sqrt((x_k-d_x)*(x_k-d_x) + (y_k-d_y)*(y_k-d_y) + delta_i) << endl;

    return sqrt((x_k-d_x)*(x_k-d_x) + (y_k-d_y)*(y_k-d_y) + delta_i);


}

template <typename T, typename F>
F MultiQuadricInterpolator<T,F>::norm(F x1, F x2) const{
    return sqrt((x2-x1)*(x2-x1));
}
