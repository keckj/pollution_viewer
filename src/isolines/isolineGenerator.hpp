
#ifndef ISOLINES_H
#define ISOLINES_H

#include "utils.hpp"
#include "coords.hpp"
#include "isolineUtils.hpp"

template <typename F, unsigned int N>
class IsoLineGenerator {
    
    public:
        IsoLineGenerator(unsigned int dataWidth, unsigned int dataHeight, BoundingBox<double> bbox);

        ColorLineList<double,N> generateIsoline(F* density, double isovalue, Color<N> color);

        void test();

    private:
        unsigned char computeCase(double d[], double isovalue);

        void attachLine(Line<double> &line, LineList<double> &lineList);

        unsigned int dataWidth, dataHeight;
        BoundingBox<double> bbox;

};

#include "isolineGenerator.tpp"

#endif /* end of include guard: ISOLINES_H */
