
#ifndef LINES_H
#define LINES_H

#include <list>
#include <cassert>
#include "vec.hpp"
#include "colors.hpp"
#include "coords.hpp"

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

#endif /* end of include guard: LINES_H */
