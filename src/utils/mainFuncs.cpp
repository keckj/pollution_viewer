
#include "mainFuncs.hpp"

namespace mainFuncs {

    void init() {

        // Initialize static global vars
        initColorizers();

        // Initialize Logs
        using log4cpp::log_console;
        log4cpp::initLogs();
        log_console->infoStream() << " *** Projet de visualisation *** ";
        log_console->infoStream() << "[Init] Logs init";

        // Initialize DevIL
        ilInit();
        log_console->infoStream() << "[Init] DevIL init";
    }


    SensorDataArr parseSensorData() {
        // Parse stations
        StationParser sp;
        std::map<std::string, Station*> stations = sp.parse(stationDataFile);

        // Parse sensor data
        DataParser dp;
        dp.parseSensorData(sensorDataFile, stations);

        // Change data layout of a given sensor (AoS to SaO)
        return buildSensorDataArray(stations, sensorName);
    }

    InterpData interpolateData(const SensorDataArr &sensorData) {
        
        unsigned int nData = std::min(maxDataProcessed, sensorData.nMeasures);
        log4cpp::log_console->infoStream() << "[Interpolation] Interpolating " << nData << " out of " << sensorData.nMeasures << " measures with " << nInterpolators << " different interpolators !";

        InterpData interpolatorInterpolatedDataMap;
        for (unsigned int k = 0; k < nInterpolators; k++) {
            log4cpp::log_console->infoStream() << "[Interpolation] \tInterpolating with interpolator " << interpolatorNames[k] << "...";
            std::vector<InterpolatedData<float>> interpolatorInterpolatedData(nData);
            for (unsigned int i = 0; i < nData; i++) {
                interpolatorInterpolatedData[i] =
                        (*interpolators[k])(gridWidth,gridHeight,sensorData.nStations, sensorData.x, sensorData.y, sensorData.data[i]);
            }
            interpolatorInterpolatedDataMap.emplace(interpolatorNames[k], interpolatorInterpolatedData); 
        }

        return interpolatorInterpolatedDataMap;
    }

    void generateScreenOverlays(const SensorDataArr &sensorData, const InterpData &interpolatedDataGrid) {
        unsigned int nData = std::min(maxDataProcessed, sensorData.nMeasures);
        log4cpp::log_console->infoStream() << "[Screen Overlays] Generating " << nInterpolators << " x " << nData << " = " << nInterpolators*nData << " screen overlays...";
        
        for (unsigned int k = 0; k < nInterpolators; k++) {
            const std::string interpolatorName = interpolatorNames[k];
            for (unsigned int i = 0; i < nData; i++) {
                dataColorizer->resetMinMax(interpolatedDataGrid.at(interpolatorName)[i]);
                dataColorizer->generateColorRange(
                        kmlFolder+screenOverlayFolder,
                        screenOverlayPrefix+interpolatorName+"_"+std::to_string(i),
                        screenOverlayImgExt,
                        fontPath);
            }
        }
    }

    void generateGroundOverlays(const SensorDataArr &sensorData, const InterpData &interpolatedDataGrid) {
        unsigned int nData = std::min(maxDataProcessed, sensorData.nMeasures);
        log4cpp::log_console->infoStream() << "[Ground Overlays] Generating " << nInterpolators << " x " << nData << " = " << nInterpolators*nData << " ground overlays...";
        for (unsigned int k = 0; k < nInterpolators; k++) {
            const std::string interpolatorName = interpolatorNames[k];
            for (unsigned int i = 0; i < nData; i++) {
                const InterpolatedData<float> &data = interpolatedDataGrid.at(interpolatorName)[i];
                dataColorizer->resetMinMax(data);
                OverlayGenerator::generateImage<float,4u>(data, *dataColorizer, 
                        kmlFolder+groundOverlayFolder,groundOverlayPrefix+interpolatorName+"_"+std::to_string(i),groundOverlayImgExt);
            }
        }
    }

    IsoLines generateIsolines(const SensorDataArr &sensorData, const InterpData &interpolatedDataGrid) {
        log4cpp::log_console->infoStream() << "[Isolines] Generating isolines...";
        unsigned int nData = std::min(maxDataProcessed, sensorData.nMeasures);
    
        IsoLines interpolatorIsolineMap;
        IsoLineGenerator<float,4u> isolineGenerator(sensorData.bbox);
        
        for (unsigned int k = 0; k < nInterpolators; k++) {
            const std::string interpolatorName = interpolatorNames[k];
            std::vector<IsoLineList<double,4u,float>> interpolatorIsolines(nData);
            for (unsigned int i = 0; i < nData; i++) {
                const InterpolatedData<float> &data = interpolatedDataGrid.at(interpolatorName)[i];
                isolineColorizer->resetMinMax(data);
                interpolatorIsolines[i] = isolineGenerator.generateIsolines(data, nIsoLevels, *isolineColorizer);
            }
            interpolatorIsolineMap.emplace(interpolatorName, interpolatorIsolines); 
        }

        return interpolatorIsolineMap;
    }

    IsoContours generateIsocontours(const SensorDataArr &sensorData, const InterpData &interpolatedDataGrid, const IsoLines &isolines) {
        log4cpp::log_console->infoStream() << "[Isocontours] Generating isocontours...";
        unsigned int nData = std::min(maxDataProcessed, sensorData.nMeasures);
    
        IsoContours interpolatorIsocontourMap;
        IsoLineGenerator<float,4u> isolineGenerator(sensorData.bbox);
        
        for (unsigned int k = 0; k < nInterpolators; k++) {
            const std::string interpolatorName = interpolatorNames[k];
            std::vector<IsoContourList<double,4u,float>> interpolatorIsolines(nData);
            for (unsigned int i = 0; i < nData; i++) {
                const InterpolatedData<float> &data = interpolatedDataGrid.at(interpolatorName)[i];
                isolineColorizer->resetMinMax(data);
                interpolatorIsolines[i] = isolineGenerator.generateIsoContours(isolines.at(interpolatorName)[i], data, *isolineColorizer);
            }
            interpolatorIsocontourMap.emplace(interpolatorName, interpolatorIsolines); 
        }

        return interpolatorIsocontourMap;
    }

    void generateKmlFile(const SensorDataArr &sensorData, 
            const InterpData &interpolatedDataGrid,
            const IsoLines &isolines,
            const IsoContours &isocontours) {

        log4cpp::log_console->infoStream() << "[KML] Generating the KML file...";

        KmlGenerator::KmlGenerator kml(sensorData,
                interpolatedDataGrid,
                isolines, 
                isocontours);
    }

    //void clean(SensorDataArr &sensorData, InterpData &interpolatedDataGrid) {
        //log4cpp::log_console->infoStream() << "Done ! Cleaning Up...";
        //delete [] interpolatedDataGrid.density;
    //}
}
