

#ifndef KMLFILE_H
#define KMLFILE_H

#include <iostream>
#include <sstream>
#include <fstream>

#include "colors.hpp"

enum AltitudeMode {
    CLAMP_TO_GROUND=0,
    CLAMP_TO_SEA_FLOOR,
    RELATIVE_TO_GROUND,
    RELATIVE_TO_SEA_FLOOR,
    ABSOLUTE // <=> RELATIVE_TO_SEA_LEVEL
}

enum ColorMode {
    NORMAL=0,
    RANDOM
}

class KmlFile {

    using cstring = const std::string &;

    public:
        KmlFile(cstring filePath);
        ~KmlFile();
        
        void startKml();
        void startDocument();
        void startPlacemark();
        void startStyle(cstring styleId = std::string(""));
        void startIconStyle();
        void startLineStyle();
        void startPolyStyle();
        
        void startPoint();
        void startLineString();
        void startLinearRing();
        void startPolygon();
        
        void putName(cstring name);
        void putDescription(cstring description);
        void putStyleUrl(cstring styleId);
        void putIcon(cstring href);
        void putVisibility(bool visible);
        void putExtrude(bool extrude);
        void putTesselate(bool tesselate);
        void putWidth(unsigned int width);
        void putCoordinate(float longitude, float latitude, float height);
        void putCoordinates(unsigned int count, float *longitude, float *latitude);
        void putCoordinates(unsigned int count, float *longitude, float *latitude, float *height);
        void putColor(ColorRGBA color);
        void putColorMode(ColorMode colorMode);
        void putAltitudeMode(AltitudeMode altitudeMode);
        void putLatLonBox(BoundingBox<float> bbox, float rotation = 0.0f);

        void endPolygon();
        void endLinearRing();
        void endLineString();
        void endPoint();

        void endPolyStyle();
        void endLineStyle();
        void endIconStyle();
        void endStyle();
        void endPlacemark();
        void endDocument();
        void endKml();
        
    private:
        unsigned int indentLevel;
        std::string filePath;
        
        std::ofstream file;
        std::stringstream kml;
        
        void removeTab();
        const std::string newLineAndIndent();
        const std::string newLine();
        const std::string newLineAndDedent();
};


#endif /* end of include guard: KMLFILE_H */
