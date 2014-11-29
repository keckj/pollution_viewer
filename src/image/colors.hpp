#ifndef COLORS_H
#define COLORS_H


#include <ostream>
#include <sstream>
#include <cstring>
#include <string>
#include <iomanip>
#include <cmath>

template <unsigned int N>
struct Color {
    
    unsigned char operator[](unsigned int k) const;
    unsigned char & operator[](unsigned int k);

    std::string toHexString() const;
    
    static unsigned int channels; //duplicate of N but more clear for Muggles
    
    template <typename F>
    static Color<N> linearInterp(F alpha, const Color<N> &c1, const Color<N> &c2);

    static Color<4u> RGBtoCIE(const Color<4u> &RGB);
    static Color<4u> CIEtoRGB(const Color<4u> &LcH);


protected:
    Color();
private:
    unsigned char intensities[N];
    static double PivotXyz(const double &n);

    // reference white
    static constexpr double xr = 99.1858;
    static constexpr double yr = 100.0000;
    static constexpr double zr =  67.3938;
};

struct ColorGrayscale : public Color<1u> {
    unsigned char &p = this->operator[](0);

    ColorGrayscale(unsigned char p) {
        this->p = p;
    }

    static const ColorGrayscale white;
    static const ColorGrayscale black;
};

struct ColorRGB : public Color<3u> {
    unsigned char &r = this->operator[](0);
    unsigned char &g = this->operator[](1);
    unsigned char &b = this->operator[](2);
    
    ColorRGB(unsigned char r, unsigned char g, unsigned char b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    static const ColorRGB white;
    static const ColorRGB red;
    static const ColorRGB green;
    static const ColorRGB blue;
    static const ColorRGB black;
};

struct ColorRGBA : public Color<4u> {
    unsigned char &r = this->operator[](0);
    unsigned char &g = this->operator[](1);
    unsigned char &b = this->operator[](2);
    unsigned char &a = this->operator[](3);

    ColorRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    static const ColorRGBA white;
    static const ColorRGBA red;
    static const ColorRGBA green;
    static const ColorRGBA blue;
    static const ColorRGBA black;
};

template <unsigned int N>
Color<N>::Color() {
    memset(&intensities, 0, N*sizeof(unsigned char));
}
    
template <unsigned int N>
unsigned char Color<N>::operator[](unsigned int k) const {
    return intensities[k];
}

template <unsigned int N>
unsigned char & Color<N>::operator[](unsigned int k) {
    return intensities[k];
}
    
template <unsigned int N>
unsigned int Color<N>::channels = N;

template <unsigned int N>
std::string Color<N>::toHexString() const {
    std::stringstream ss;

    ss << std::internal << std::setfill('0') << std::hex;

    for (unsigned int k = 0; k < N; k++) {
        ss << static_cast<unsigned int>(intensities[k]);
    }

    return ss.str();
}
    
template <unsigned int N>
template <typename F>
Color<N> Color<N>::linearInterp(F alpha, const Color<N> &c1, const Color<N> &c2) {
    Color<N> res;

    for (unsigned int k = 0; k < N; k++) {
        res[k] = static_cast<unsigned char>(alpha*c1[k] + (F(1) - alpha)*c2[k]);
    }

    return res;
}

template <unsigned int N>
std::ostream & operator << (std::ostream &os, const Color<N> &c) {
    
    std::stringstream ss;

    ss << "(";
    for (unsigned int k = 0; k < N-1; k++) {
        ss << static_cast<unsigned int>(c[k]) << ",";
    }
    ss << static_cast<unsigned int>(c[N-1]);
    ss << ")";
    
    os << ss.str();
    
    return os;
}


template <unsigned int N>
double Color<N>::PivotXyz(const double &n){ 

  double Epsilon = 216.0/24389;
  double Kappa = 24389.0/27;
  return n > Epsilon ? sqrt(n) : (Kappa * n + 16) / 116;
}

template <unsigned int N>
Color<4u> Color<N>::RGBtoCIE(const Color<4u> &RGB) {
    double r,g,b;
    r = static_cast<double>(RGB[0]) / 255;
    g = static_cast<double>(RGB[1]) / 255;
    b = static_cast<double>(RGB[2]) / 255;
    const unsigned char alpha = RGB[3];

    // RGB to XYZ
    double X,Y,Z;
    X = 2.768892*r + 1.0*g + 0.0*b;
    Y = 1.751758*r + 4.5907*g + 0.056508*b;
    Z = 1.1302*r + 0.0601*g + 5.594292*b;

    // XYZ to CIE Lab
    // reference white
    // xr,yr,zr
    // internediate transformation
    double x,y,z;
    x = Color<4u>::PivotXyz(X/xr);
    y = Color<4u>::PivotXyz(Y/yr);
    z = Color<4u>::PivotXyz(Z/zr);

    double L,a;
    L = std::max(0.0, 116.0 * y - 16.0);
    a = 500.0 * (x - y);
    b = 200.0 * (y - z);

    // CIE Lab to CIE LcH
    double c,H;
    c = sqrt(a*a+b*b);
    H = atan2(b,a);
    // rad to degres
    if (H > 0){
        H = (H/M_PI) * 180.0;
    } else {
        H = 360 - (abs(H)/M_PI)*180.0;
    }
    if (H<0){
        H += 360.0;
    } else if (H>=360.0){
        H -= 360.0;
    }
    H *= 180.0 / M_PI;


    Color<4u> LcH;
    LcH[0] = static_cast<unsigned char>(L * 255);
    LcH[1] = static_cast<unsigned char>(c * 255);
    LcH[2] = static_cast<unsigned char>(H * 255);
    LcH[3] = alpha;

    return LcH;
}

template <unsigned int N>
Color<4u> Color<N>::CIEtoRGB(const Color<4u> &LcH) {

    double L,c,H;
    L = static_cast<double>(LcH[0]) / 255;
    c = static_cast<double>(LcH[1]) / 255;
    H = static_cast<double>(LcH[2]) / 255;
    const unsigned char alpha = LcH[3];


    // CIE LHc to CIE Lab
    double Hrad,a,b;
    Hrad = (H * M_PI)/180.0; // Hrad in -pi,pi
    a = cos(Hrad)*c;
    b = sin(Hrad)*c;

    // CIE Lab to XYZ
    double X,Y,Z;
    // reference white
    // xr,yr,zr

    // intermediate transformation
    double y = (L + 16.0) / 116.0;
    double x = a / 500.0 + y;
    double z = y - b / 200.0;


    double Epsilon = 216.0/24389;
    double Kappa = 24389.0/27;
    double x3 = x * x * x;
    double z3 = z * z * z;
    X = xr * (x3 > Epsilon ? x3 : (x - 16.0 / 116.0) / 7.787);
    Y = yr * (L > (Kappa * Epsilon) ? pow(((L + 16.0) / 116.0), 3.0) : L / Kappa);
    Z = zr * (z3 > Epsilon ? z3 : (z - 16.0 / 116.0) / 7.787);


    // XYZ to RGB
    double R,G,B;
    // L,c,H
    R = 0.418456*X -0.091167*Y + 0.00092*Z;
    G = -0.158657*X + 0.252426*Y -0.002550*Z;
    B = -0.082833*X + 0.015707*Y + 0.178595*Z;


    Color<4u> RGB;
    RGB[0] = static_cast<unsigned char>(R * 255);
    RGB[1] = static_cast<unsigned char>(G * 255);
    RGB[2] = static_cast<unsigned char>(B * 255);
    RGB[3] = alpha;

    return RGB;
}

std::ostream & operator << (std::ostream &os, const Color<1u> &c);

#endif /* end of include guard: COLORS_H */

