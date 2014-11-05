
#ifndef STATIONTYPE_H
#define STATIONTYPE_H

#include <ostream>

class StationType {

    public:
        enum STATION_TYPE {
            URBAIN,
            PERIURBAIN,
            RURALE,
            INDUSTRIELLE,
            TRAFIC
        };

        StationType();
        StationType(const StationType &st);
        StationType(const std::string &type);

        StationType& operator= (const StationType &st);
        StationType& operator= (const std::string &type);

        const std::string toString() const;

    private:
        STATION_TYPE _type;
};
    
std::ostream & operator<< (std::ostream &os, const StationType &st);  

#endif /* end of include guard: STATIONTYPE_H */
