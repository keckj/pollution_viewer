

#ifndef CONFIG_H
#define CONFIG_H

#include "colors.hpp"
#include "linearColorizer.hpp"
#include "simpleShepardInterpolator.hpp"

namespace Globals {
    // Parsing
    static const std::string stationDataFile = "data/stations.data";
    static const std::string sensorDataFile = "data/particules.data";
    static const std::string sensorName("Particules PM10");

    // Interpolation
    static const unsigned int maxDataProcessed = 100u;
    static const unsigned int gridWidth = 64u;
    static const unsigned int gridHeight = 64u;

    static const SimpleShepardInterpolator<int,float> I1(2.0);
    static const SimpleShepardInterpolator<int,float> I2(2.0);

    static const unsigned int nInterpolators = 2u;
    static const unsigned int defaultVisibleInterpolatorId = 0u;
    static const Interpolator<int,float>* interpolators[nInterpolators] = { &I1, &I2 };
    static const std::string interpolatorNames[nInterpolators] = { "shepard1", "shepard2" };
   
    // Data generation parameters
    static LinearColorizer<float,4u> dataColorizer(ColorRGBA(255,0,0,255),ColorRGBA(0,0,255,50));
    static LinearColorizer<float,4u> isolineColorizer(ColorRGBA::blue,ColorRGBA::red);
    static LinearColorizer<float,4u> isocontourColorizer(ColorRGBA::red,ColorRGBA::blue);
    static const unsigned int nIsoLevels = 10u;
    static const std::string fontPath =  "fonts/FreeMonoBold.ttf";

    // Kml generation parameters
    static const std::string kmlFolder = "kml/";
    static const std::string kmlFileName = "root.kml";
    static const std::string stationIconHref = "kml/icons/station.png";

    static const std::string screenOverlayFolder = "kml/screenOverlays/";
    static const std::string screenOverlayPrefix = "screen_overlay_";
    static const std::string screenOverlayImgExt = "png";

    static const std::string groundOverlayFolder = "kml/groundOverlays/";
    static const std::string groundOverlayPrefix = "ground_overlay_";
    static const std::string groundOverlayImgExt = "png";
}


#endif /* end of include guard: CONFIG_H */
