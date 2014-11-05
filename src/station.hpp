
#ifndef STATION_H
#define STATION_H

#include "vec.hpp"
#include "stationType.hpp"

struct Station {
        std::string name;
        StationType type;
        Vec<double> location;
};

#endif /* end of include guard: STATION_H */
