
#include "colors.hpp"

std::ostream & operator << (std::ostream &os, const ColorMonochrome &c) {
    os << static_cast<unsigned int>(c.p);
    return os;
}

std::ostream & operator << (std::ostream &os, const ColorRGB &c) {
    os << "(" << static_cast<unsigned int>(c.r) << "," << static_cast<unsigned int>(c.g) << "," << static_cast<unsigned int>(c.b) << ")";
    return os;
}

std::ostream & operator << (std::ostream &os, const ColorRGBA &c) {
    os << "(" << static_cast<unsigned int>(c.r) << "," << static_cast<unsigned int>(c.g) << "," << static_cast<unsigned int>(c.b) << "," << static_cast<unsigned int>(c.a) << ")";
    return os;
}
