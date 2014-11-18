

#ifndef KMLFILE_H
#define KMLFILE_H

#include <iostream>
#include <sstream>
#include <fstream>

#include "colors.hpp"

class KmlFile {

    using cstring = const std::string &;

    public:
        KmlFile(std::string filePath);
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
        
        void putName(cstring name);
        void putDescription(cstring description);
        void putStyleId(cstring styleId);
        void putAltitudeMode(cstring altitudeMode);
        void putIcon(cstring webLink);
        void putVisibility(bool visible);
        void putTesselate(bool tesselate);
        void putCoordinate(float longitude, float latitude, float height);
        void putCoordinates(unsigned int count, float *longitude, float *latitude, float *height);
        void putColor(ColorRGBA color);

        void endPoint();
        void endLineString();

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
