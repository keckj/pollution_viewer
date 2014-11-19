

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

    std::string stationDescription(unsigned int i, unsigned int indentLevel) {
   
        std::stringstream ss;
        std::string tabsMinusOne, tabs;
        for (unsigned int i = 0; i < indentLevel; i++) {
            if(i==indentLevel-2)
               tabsMinusOne = ss.str();

            ss << "\t";
        }
        tabs = ss.str();

        std::stringstream description;
        assert(i < nStations);
        description << std::endl;
        description << tabs << "<![CDATA[" << std::endl;
        description << tabs << "<h3>Station " << *stationNames[i] << "</h3>" << std::endl;
        description << tabs << "<b>Type de la station:</b> " << stationTypes[i] << std::endl;
        description << tabs << "<br/><b>Longitude:</b> <i>" << x[i] << "</i>" << std::endl;
        description << tabs << "<br/><b>Latitude:</b>  <i>" << y[i] << "</i>" << std::endl;
        description << tabs << "]]>";
        description << std::endl;
        description << tabsMinusOne;
        
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
