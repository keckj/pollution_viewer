#ifndef ISOLINE_H
#define ISOLINE_H

#include "lines.hpp"

template <typename T, unsigned int N, typename F>
struct IsoLine {
    ColorMultiLine<T,N> lines;
    F value;

    IsoLine() : lines(), value(0) {};
    IsoLine(const MultiLine<T> lines, const Color<N> &color, F value) : lines(ColorMultiLine<T,N>(lines,color)), value(value) {};
    IsoLine(const ColorMultiLine<T,N> &colorLines, F value) : lines(lines), value(value) {};
};

template <typename T, unsigned int N, typename F>
using IsoLineList = std::list<IsoLine<T,N,F>>;

#endif /* end of include guard: ISOLINE_H */
