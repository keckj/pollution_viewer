
#include "colors.hpp"

std::ostream & operator << (std::ostream &os, const ColorGrayscale &c) {
    os << static_cast<unsigned int>(c.p);
    return os;
}

const ColorGrayscale ColorGrayscale::white(0xff);
const ColorGrayscale ColorGrayscale::black(0);

const ColorRGB ColorRGB::white(0xff,0xff,0xff);
const ColorRGB ColorRGB::red(0xff,0,0);
const ColorRGB ColorRGB::green(0,0xff,0);
const ColorRGB ColorRGB::blue(0,0,0xff);
const ColorRGB ColorRGB::black(0,0,0);
    
const ColorRGBA ColorRGBA::white(0xff,0xff,0xff,0xff);
const ColorRGBA ColorRGBA::red(0xff,0,0,0xff);
const ColorRGBA ColorRGBA::green(0,0xff,0,0xff);
const ColorRGBA ColorRGBA::blue(0,0,0xff,0xff);
const ColorRGBA ColorRGBA::black(0,0,0,0xff);
