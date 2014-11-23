
#ifndef LINES_H
#define LINES_H

#include <list>
#include "vec.hpp"
#include "interpolator.hpp"

template <typename T>
using Point = std::list<Vec<T>>;

template <typename T>
using PointList = std::list<Vec<T>>;

template <typename T>
using Line = std::list<Vec<T>>;

template <typename T>
using MultiLine = std::list<Line<T>>;

template <typename T>
using MultiLineList = std::list<MultiLine<T>>;

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

template <typename T, unsigned int N>
struct ColorMultiLine {
    MultiLine<T> lines;
    Color<N> color;

    ColorMultiLine() : lines(), color() {};
    ColorMultiLine(const Color<N> &color) : lines(), color(color) {};
    ColorMultiLine(const MultiLine<T> &lines, const Color<N> &color) : lines(lines), color(color) {};
};

template <typename T, unsigned int N>
using ColorMultiLineList = std::list<ColorMultiLine<T,N>>;

template <typename T, unsigned int N, typename F>
struct IsoLine {
    ColorMultiLine<T,N> lines;
    F value;

    IsoLine() : lines(), value(0) {};
    IsoLine(const MultiLine<T> lines, const Color<N> &color, F value) : lines(ColorMultiLine<T,N>(lines,color)), value(value) {};
    IsoLine(const ColorMultiLine<T,N> &colorLines, F value) : lines(lines), value(value) {};
};

template <typename T, unsigned int N, typename F>
struct Isocontour {
    MultiLine<T> lines;
    Color<N> color;
    F value;

    Isocontour(const IsoLine<T,N,F> &isoline, const InterpolatedData<F> &data);
};

template <typename T, unsigned int N, typename F>
using IsoLineList = std::list<IsoLine<T,N,F>>;

template <typename T, unsigned int N, typename F>
using IsoContourList = std::list<Isocontour<T,N,F>>;

#endif /* end of include guard: LINES_H */
