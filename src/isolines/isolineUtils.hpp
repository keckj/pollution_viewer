
#ifndef ISOLINEUTILS_H
#define ISOLINEUTILS_H

#include <list>
#include "vec.hpp"

template <typename T>
using Point = std::list<Vec<T>>;

template <typename T>
using PointList = std::list<Vec<T>>;

template <typename T>
using Line = std::list<Vec<T>>;

template <typename T>
using LineList = std::list<Line<T>>;

template <typename T, unsigned int N>
struct ColorLine {
    Line<T> line;
    Color<N> color;

    ColorLine() : line(), color() {};
    ColorLine(const Color<N> &color) : line(), color(color) {};
    ColorLine(const Line<T> &line, const Color<N> &color) : line(line), color(color) {};
};

template <typename T, unsigned int N>
using ColorLineList = std::list<ColorLine<T,N>>;

namespace MarchingSquare {
    static unsigned char lineCount[16] = {
        0,1,1,1,
        1,2,1,1,
        1,1,2,1,
        1,1,1,0
    };

    //max 2*2 vertices
    static char lineTable[64] = {
            -1,-1,-1,-1, // 0
            0,3,-1,-1,   // 1
            0,1,-1,-1,   // 1
            1,3,-1,-1,   // 1

            1,2,-1,-1,   // 1
            1,2,3,0,     // 2
            0,2,-1,-1,   // 1
            2,3,-1,-1,   // 1

            2,3,-1,-1,   // 1
            0,2,-1,-1,   // 1
            1,2,3,0,     // 2
            1,2,-1,-1,   // 1

            1,3,-1,-1,   // 1
            0,1,-1,-1,   // 1
            0,3,-1,-1,   // 1
            0,0,-1,-1,   // 0
    };

    //(X,Y)
    static double edgeStart[8] = {
        0.0, 0.0, 
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0
    };

    //(X,Y)
    static double edgeEnd[8] = { 
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0,
        0.0, 0.0 
    };
    
    //(VX,VY)
    static double edgeDir[8] = { 
        1.0, 0.0,
        0.0, 1.0,
        -1.0, 0.0,
        0.0, -1.0
    };
}

#endif /* end of include guard: ISOLINEUTILS_H */
