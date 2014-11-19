#ifndef COORDS_H
#define COORDS_H

#include <limits>

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

#endif /* end of include guard: COORDS_H */
