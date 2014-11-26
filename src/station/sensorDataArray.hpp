

#ifndef SENSORDATAARRAY_H
#define SENSORDATAARRAY_H

#include <ctime>
#include <cassert>
#include <string>
#include <cstring>

#include "coords.hpp"
#include "station.hpp"

template <typename T>
struct SensorDataArray {
    const std::string sensorName;
    const std::string unitName;

    const std::tm startTime;
    const std::tm endTime;
    const std::tm deltaT;

    const unsigned int nMeasures;
    const unsigned int nStations;

    const std::string **stationNames;
    StationType *stationTypes;
    double *x;
    double *y;
    double *z;
    T **data;
    
    BoundingBox<double> bbox;

    //DATA LAYOUT
    //00:00:00 s1 s2 s3 s4 ... s_nStations <= first measure
    //00:01:00 s1 s2 s3 s4 ... s_nStations
    //00:02:00 s1 s2 s3 s4 ... s_nStations
    //.. nMeasures times
    //xx:xx:xx s1 s2 s3 s4 ... s_nStations <= last measure
    
    SensorDataArray();

    SensorDataArray(std::string sensorName, std::string unitName, 
            std::tm startTime, std::tm endTime, std::tm deltaT, 
            unsigned int nMeasures, unsigned int nStations,
            const std::string **stationNames, StationType *stationTypes,
            double *x, double *y, double *z,
            T** data);

    std::tm getTime(unsigned int k) const {

        int kk = static_cast<int>(k);
        int sec  = startTime.tm_sec  + kk *deltaT.tm_sec;
        int min  = startTime.tm_min  + kk *deltaT.tm_min  + sec  / 60;
        int hour = startTime.tm_hour + kk *deltaT.tm_hour + min  / 60;
        int mday = startTime.tm_mday + kk *deltaT.tm_mday + hour / 24;
        int mon  = startTime.tm_mon  + kk *deltaT.tm_mon  + mday / 31;
        int year = startTime.tm_year + kk *deltaT.tm_year + mon  / 12;
    
        char* date = new char[100];
        strftime(date, 100, "%d/%m/%Y %H:%M:%S", &startTime);
        std::cout << date << std::endl;
        std::cout << mday << "/" << mon+1 << "/" << 1900+year << "  " << hour << ":" << min << ":" << sec << std::endl;

        std::tm TIME;
        memset(&TIME, 0, sizeof(std::tm));
        TIME.tm_sec = sec%60;
        TIME.tm_min = min%60;
        TIME.tm_hour = hour%24;
        TIME.tm_mday = mday%31;
        TIME.tm_mon = mon%12;
        TIME.tm_year = year;
        
        return TIME;
    }

    std::string stationDescription(unsigned int i, unsigned int indentLevel) const {
   
        std::stringstream ss;
        std::string tabsMinusOne, tabs;
        for (unsigned int i = 0; i < indentLevel; i++) {
            if(i==indentLevel-1)
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
        if(data[0][i] >= T(0))
            description << tabs << "<br/><b>" << sensorName << ":</b>  <i>" << data[0][i] << " " << unitName <<"</i>" << std::endl;
        else
            description << tabs << "<br/><b>" << sensorName << ":</b>  <i>no data</i>" << std::endl;
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
    bbox = computeBoundingBox(Coords<double>(nStations, x, y));
}


#endif /* end of include guard: SENSORDATAARRAY_H */
