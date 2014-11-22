
#ifndef ISOLINES_H
#define ISOLINES_H

#include "coords.hpp"
#include "isolineUtils.hpp"

template <typename F, unsigned int N>
class IsoLineGenerator {
    
    public:
        IsoLineGenerator(unsigned int dataWidth, unsigned int dataHeight, BoundingBox<double> bbox);

        ColorLineList<double,N> generateIsoline(F* density, F isovalue, Color<N> color);

    private:
        unsigned char computeCase(F d[], F isovalue);

        unsigned int dataWidth, dataHeight;
        BoundingBox<double> bbox;

};

#include "isolineGenerator.tpp"

#endif /* end of include guard: ISOLINES_H */
