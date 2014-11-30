

#ifndef CONFIG_H
#define CONFIG_H

#include "colors.hpp"
#include "linearColorizer.hpp"
#include "simpleShepardInterpolator.hpp"
#include "multiQuadricInterpolator.hpp"

namespace Globals {
    // Parsing
    static const std::string stationDataFile = "data/stations.data";
    static const std::string sensorDataFile = "data/particules.data";
    static const std::string sensorName("Particules PM10");

    // Interpolation
    static const unsigned int maxDataProcessed = 1u;
    static const unsigned int gridWidth = 1024u;
    static const unsigned int gridHeight = 1024u;

    static const SimpleShepardInterpolator<int,float> I1(2.0);
    // static const MultiQuadricInterpolator<int,float> I1(std::pow(10,-12),std::pow(10,-4));
    static const MultiQuadricInterpolator<int,float> I2(std::pow(10,-12),std::pow(10,-4));

    static const unsigned int nInterpolators = 2u;
    static const Interpolator<int,float>* interpolators[nInterpolators] = { &I1, &I2 };
    static const std::string interpolatorNames[nInterpolators] = { "shepard1", "multiquadrics" };
    static const std::string defaultVisibleInterpolatorId = "shepard1";
   
    // Data generation parameters
    static Colorizer<float,4u> *dataColorizer;
    static Colorizer<float,4u> *isolineColorizer;
    static Colorizer<float,4u> *isocontourColorizer;
    static void initColorizers() { // those variables are static initialization order dependent
        dataColorizer = new LinearColorizer<float,4u>(ColorRGBA(255,0,0,255),ColorRGBA(0,0,255,50));
        isolineColorizer = new LinearColorizer<float,4u>(ColorRGBA::blue,ColorRGBA::red);
        isocontourColorizer = new LinearColorizer<float,4u>(ColorRGBA::red,ColorRGBA::blue);
    }

    static const unsigned int nIsoLevels = 10u;
    static const std::string fontPath =  "fonts/FreeMonoBold.ttf";

    // Kml generation parameters
    static const std::string kmlFolder = "kml/";
    static const std::string kmlFileName = "root.kml";
    static const std::string stationIconHref = "icons/antenna.png";

    static const std::string screenOverlayFolder = "screenOverlays/";
    static const std::string screenOverlayPrefix = "screen_overlay_";
    static const std::string screenOverlayImgExt = "png";

    static const std::string groundOverlayFolder = "groundOverlays/";
    static const std::string groundOverlayPrefix = "ground_overlay_";
    static const std::string groundOverlayImgExt = "png";
}


#endif /* end of include guard: CONFIG_H */
