#ifndef COLORS_H
#define COLORS_H

#include <ostream>

struct Color {
};

struct ColorMonochrome : public Color {
    unsigned char p;
    ColorMonochrome(unsigned char p) : p(p) {}
    template <typename F>
    static ColorMonochrome linearInterp(F alpha, const ColorMonochrome &c1, const ColorMonochrome &c2) {
        return ColorMonochrome(static_cast<unsigned char>(alpha*c1.p + (F(1)-alpha)*c2.p));
    }
     static unsigned int getChannelCount() { return 1u; }
};

struct ColorRGB : public Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    ColorRGB(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) {}
    template <typename F>
    static ColorRGB linearInterp(F alpha, const ColorRGB &c1, const ColorRGB &c2) {
        return ColorRGB( 
            static_cast<unsigned char>(alpha*c1.r + (F(1)-alpha)*c2.r),
            static_cast<unsigned char>(alpha*c1.g + (F(1)-alpha)*c2.g),
            static_cast<unsigned char>(alpha*c1.b + (F(1)-alpha)*c2.b));
    }
     static unsigned int getChannelCount() { return 3u; }
};

struct ColorRGBA : public Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
    ColorRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : r(r), g(g), b(b), a(a) {}
    template <typename F>
    static ColorRGBA linearInterp(F alpha, const ColorRGBA &c1, const ColorRGBA &c2) {
        return ColorRGBA( 
            static_cast<unsigned char>(alpha*c1.r + (F(1)-alpha)*c2.r),
            static_cast<unsigned char>(alpha*c1.g + (F(1)-alpha)*c2.g),
            static_cast<unsigned char>(alpha*c1.b + (F(1)-alpha)*c2.b),
            static_cast<unsigned char>(alpha*c1.a + (F(1)-alpha)*c2.a));
    }
    static unsigned int getChannelCount() { return 4u; }
};
    
std::ostream & operator << (std::ostream &os, const ColorMonochrome &c);
std::ostream & operator << (std::ostream &os, const ColorRGB &c);
std::ostream & operator << (std::ostream &os, const ColorRGBA &c);

#endif /* end of include guard: COLORS_H */
