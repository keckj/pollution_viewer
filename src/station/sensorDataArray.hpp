

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

    std::string stationDescription(unsigned int i) {
        std::stringstream description;
        assert(i < nStations);
        description << std::endl;
        description << "<![CDATA[" << std::endl;
        description << "<h3>Station " << *stationNames[i] << "</h3>" << std::endl;
        description << "<b>Type de la station:</b> " << stationTypes[i] << std::endl;
        description << "<br/><b>Longitude:</b> " << x[i] << std::endl;
        description << "<br/><b>Latitude:</b>  " << y[i] << std::endl;
        description << "]]>";
        description << std::endl;
        
        return description.str();
    }
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
