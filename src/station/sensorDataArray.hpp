

#ifndef SENSORDATAARRAY_H
#define SENSORDATAARRAY_H

#include <ctime>
#include <string>

template <typename T>
struct SensorDataArray {
    std::string sensorName;
    std::string unitName;

    std::tm startTime;
    std::tm endTime;
    std::tm deltaT;

    unsigned int nMeasures;
    unsigned int nStations;

    const std::string **stationNames;
    StationType *stationTypes;
    double *x;
    double *y;
    double *z;
    T **data;

    //DATA LAYOUT
    //00:00:00 s1 s2 s3 s4 ... s_nStations <= first measure
    //00:01:00 s1 s2 s3 s4 ... s_nStations
    //00:02:00 s1 s2 s3 s4 ... s_nStations
    //.. nMeasures times
    //xx:xx:xx s1 s2 s3 s4 ... s_nStations <= last measure

    SensorDataArray(std::string sensorName, std::string unitName, 
            std::tm startTime, std::tm endTime, std::tm deltaT, 
            unsigned int nMeasures, unsigned int nStations,
            const std::string **stationNames, StationType *stationTypes,
            double *x, double *y, double *z,
            T** data);
};


template <typename T>
SensorDataArray<T>::SensorDataArray(std::string sensorName, std::string unitName, 
            std::tm startTime, std::tm endTime, std::tm deltaT, 
            unsigned int nMeasures, unsigned int nStations,
            const std::string **stationNames, StationType *stationTypes,
            double *x, double *y, double *z,
            T** data):
    sensorName(sensorName), unitName(unitName), 
    startTime(startTime), endTime(endTime), deltaT(deltaT), 
    nMeasures(nMeasures), nStations(nStations),
    stationNames(stationNames), stationTypes(stationTypes), 
    x(x), y(y), z(z),
    data(data) 
{
}


#endif /* end of include guard: SENSORDATAARRAY_H */
