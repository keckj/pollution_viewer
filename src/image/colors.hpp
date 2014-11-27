#ifndef COLORS_H
#define COLORS_H

#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <iomanip>

template <unsigned int N>
struct Color {
    
    unsigned char operator[](unsigned int k) const;
    unsigned char & operator[](unsigned int k);

    Color& operator = (const Color &other) {
        memcpy(intensities, other.intensities, N*sizeof(unsigned char));
        return *this;
    }

    std::string toHexString() const;
    
    static unsigned int channels; //duplicate of N but more clear for Muggles
    
    template <typename F>
    static Color<N> linearInterp(F alpha, const Color<N> &c1, const Color<N> &c2);

    Color();
private:
    unsigned char intensities[N];
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

std::ostream & operator << (std::ostream &os, const Color<1u> &c);

#endif /* end of include guard: COLORS_H */

