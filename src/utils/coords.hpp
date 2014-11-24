#ifndef COORDS_H
#define COORDS_H

#include <limits>
#include "vec.hpp"

template <typename T>
struct Coords {
    unsigned int nCoords;  
    T *x;
    T *y;
    Coords(unsigned int nCoords, T* x, T* y) : nCoords(nCoords), x(x), y(y) {}
};

template <typename T>
struct BoundingBox {
    T xmin, xmax;
    T ymin, ymax;

    BoundingBox() {
        xmin = std::numeric_limits<T>::max();
        ymin = std::numeric_limits<T>::max();
        xmax = std::numeric_limits<T>::min();
        ymax = std::numeric_limits<T>::min();
    }

    BoundingBox(T xmin, T ymin, T xmax, T ymax) :
        xmin(xmin), ymin(ymin), xmax(xmax), ymax(ymax) {
    }

    Vec<T> topLeft()     const { return Vec<T>(xmin,ymax,0); }
    Vec<T> topRight()    const { return Vec<T>(xmax,ymax,0); }
    Vec<T> bottomRight() const { return Vec<T>(xmax,ymin,0); }
    Vec<T> bottomLeft()  const { return Vec<T>(xmin,ymin,0); }
    
    bool isBorder(const Vec<T> &v) const {
        using Utils::areEqual;
        return(areEqual<T>(v.x, xmin) || areEqual<T>(v.x, xmax) || areEqual<T>(v.y, ymin) || areEqual<T>(v.y, ymax));
    }
};

template <typename T>
BoundingBox<T> computeBoundingBox(const Coords<T> &coords) {
    BoundingBox<T> bbox;
    for (unsigned int i = 0; i < coords.nCoords; i++) {
        bbox.xmin = (coords.x[i] < bbox.xmin ? coords.x[i] : bbox.xmin);
        bbox.xmax = (coords.x[i] > bbox.xmax ? coords.x[i] : bbox.xmax);
        bbox.ymin = (coords.y[i] < bbox.ymin ? coords.y[i] : bbox.ymin);
        bbox.ymax = (coords.y[i] > bbox.ymax ? coords.y[i] : bbox.ymax);
    }       

    return bbox;
}

template <typename T>
Coords<T> toUnitSquare(const Coords<T> &coords) {
    BoundingBox<T> bbox = computeBoundingBox(coords);
    T* x = new T[coords.nCoords];
    T* y = new T[coords.nCoords];
    
    for (unsigned int i = 0; i < coords.nCoords; i++) {
        x[i] = (coords.x[i]-bbox.xmin)/(bbox.xmax - bbox.xmin);
        y[i] = (coords.y[i]-bbox.ymin)/(bbox.ymax - bbox.ymin);
    }       

    return Coords<T>(coords.nCoords,x,y);
}

template <typename T>
std::ostream &operator<< (std::ostream &os, const BoundingBox<T> &bbox) {
    os << "BBOX(xmin="<<bbox.xmin<<", ymin="<<bbox.ymin<<", xmax="<<bbox.xmax<<", ymax="<<bbox.ymax<<")";
    return os;
}

#endif /* end of include guard: COORDS_H */
