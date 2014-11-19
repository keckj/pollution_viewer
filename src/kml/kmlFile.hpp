

#ifndef KMLFILE_H
#define KMLFILE_H

#include <iostream>
#include <sstream>
#include <fstream>

#include "colors.hpp"
#include "coords.hpp"

enum AltitudeMode {
    CLAMP_TO_GROUND=0,
    CLAMP_TO_SEA_FLOOR,
    RELATIVE_TO_GROUND,
    RELATIVE_TO_SEA_FLOOR,
    ABSOLUTE // <=> RELATIVE_TO_SEA_LEVEL
};

enum ColorMode {
    NORMAL=0,
    RANDOM
};

enum DateFormat {
    YYYY=0,
    YYYY_MM,
    YYYY_MM_DD,
    YYYY_MM_DD_hh_mm_ss,
    YYYY_MM_DD_hh_mm_ss_zzzzzz
};

class KmlFile {

    using cstring = const std::string &;

    public:
        KmlFile(cstring filePath);
        ~KmlFile();

        //High level primitives
        void putKmlHeader();
        void putGroundOverlay(cstring name, unsigned int altitude, AltitudeMode altitudeMode, BoundingBox<double> bbox, double rotation, cstring iconPath);
        void putKmlFooter();
      
        //Low level primitives
        void startKml();
        
        void startDocument(cstring documentId = std::string(""));
        void startPlacemark(cstring placemarkId = std::string(""));
        void startGroundOverlay(cstring placemarkId = std::string(""));
        void startStyle(cstring styleId = std::string(""));
        void startIconStyle(cstring styleId = std::string(""));
        void startLineStyle(cstring styleId = std::string(""));
        void startPolyStyle(cstring styleId = std::string(""));
        
        void startPoint();
        void startLineString();
        void startLinearRing();
        void startPolygon();
        
        void putName(cstring name);
        void putAuthor(cstring author);
        void putDescription(cstring description);
        void putStyleUrl(cstring styleId);
        void putIcon(cstring href);
        void putVisibility(bool visible);
        void putExtrude(bool extrude);
        void putTesselate(bool tesselate);
        void putOpen(bool open);
        void putWidth(unsigned int width);
        void putAltitude(unsigned int altitude);
        void putCoordinate(float longitude, float latitude, float height);
        void putCoordinates(unsigned int count, float *longitude, float *latitude);
        void putCoordinates(unsigned int count, float *longitude, float *latitude, float *height);
        void putColor(ColorRGBA color);
        void putColorMode(ColorMode colorMode);
        void putAltitudeMode(AltitudeMode altitudeMode);
        void putDate(const std::tm &date, DateFormat dateFormat);
        void putTimeStamp(const std::tm &date, DateFormat dateFormat, cstring timeStampId = std::string(""));
        void putTimeSpan(const std::tm &beginDate, const std::tm &endDate, DateFormat dateFormat, cstring timeSpanId = std::string(""));
        void putLatLonBox(BoundingBox<double> bbox, double rotation = 0.0);

        void endPolygon();
        void endLinearRing();
        void endLineString();
        void endPoint();

        void endPolyStyle();
        void endLineStyle();
        void endIconStyle();
        void endStyle();
        void endPlacemark();
        void endGroundOverlay();
        void endDocument();

        void endKml();

        void skipLine();
        void jumpLines(unsigned int lineCount);
        
    private:
        unsigned int indentLevel;
        std::string filePath;
        
        std::ofstream file;
        std::stringstream kml;
       
        //helper funcs
        bool stringIsEmpty(cstring string);
        void removeTab();
        const std::string newLineAndIndent();
        const std::string newLine();
        const std::string newLineAndDedent();
        std::string dateToString(const std::tm &date, DateFormat format);
};


#endif /* end of include guard: KMLFILE_H */
