
#ifndef STATION_H
#define STATION_H

#include <map>
#include "vec.hpp"
#include "stationType.hpp"
#include "sensorData.hpp"

struct Station {
        std::string name;
        StationType type;
        Vec<double> location;
        
        Station(std::string name, StationType type, Vec<double> location);
        
        void addSensorData(SensorData<int> data);
        
        bool hasSensorData(std::string sensorName) const;
        SensorData<int> getSensorData(std::string sensorName);

    private:
        std::map<std::string, SensorData<int>> _data;

};

#endif /* end of include guard: STATION_H */
