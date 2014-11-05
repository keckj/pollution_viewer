
#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <ctime>
#include <string>
#include <vector>

template <typename T>
struct SensorData {
    std::string sensorName;
    std::string unitName;

    std::tm startTime;
    std::tm endTime;
    std::tm deltaT;

    unsigned int nData;
    std::vector<T> data;

    SensorData(std::string sensorName, std::string unitName, 
            std::tm startTime, std::tm endTime, std::tm deltaT, 
            std::vector<T> data);
};


template <typename T>
SensorData<T>::SensorData(std::string sensorName, std::string unitName, 
            std::tm startTime, std::tm endTime, std::tm deltaT, 
            std::vector<T> data) :
    sensorName(sensorName), unitName(unitName), 
    startTime(startTime), endTime(endTime), deltaT(deltaT), 
    data(data) 
{
}


#endif /* end of include guard: SENSORDATA_H */
