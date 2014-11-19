

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


enum HotSpotUnit {
    NONE,
    PIXELS,
    INSET_PIXELS,
    FRACTION
};

union HotSpotValue {
    int i;
    float f;
    HotSpotValue(float f) : f(f) {}
    HotSpotValue(int i) : i(i) {}
};

struct HotSpot {
    HotSpotValue x, y;
    HotSpotUnit ux, uy;

    HotSpot() : x(0), y(0), ux(NONE), uy(NONE) {}
    explicit HotSpot(float x, float y) : x(x), y(y), ux(FRACTION), uy(FRACTION) {}
    explicit HotSpot(int x, HotSpotUnit ux, float y) : x(x), y(y), ux(ux), uy(FRACTION) {}
    explicit HotSpot(float x, int y, HotSpotUnit uy) : x(x), y(y), ux(FRACTION), uy(uy) {}
    explicit HotSpot(int x, HotSpotUnit ux, int y, HotSpotUnit uy) : x(x), y(y), ux(ux), uy(uy) {}
    
    static const std::string strUnit(HotSpotUnit unit) {
        switch(unit) {
            case PIXELS:
                return "pixels";
            case INSET_PIXELS:
                return "insetPixels";
            case FRACTION:
                return "fraction";
            default:
                return "";
        }
    }

    const std::string strX() const {
        std::stringstream ss;
        if(ux == FRACTION)
            ss << x.f;
        else 
            ss << x.i;
        return ss.str();
    }

    const std::string strY() const {
        std::stringstream ss;
        if(uy == FRACTION)
            ss << y.f;
        else 
            ss << y.i;
        return ss.str();
    }
   
    const std::string strUX() const {
        return strUnit(ux);
    }
    
    const std::string strUY() const {
        return strUnit(uy);
    }
};

class KmlFile {

    using cstring = const std::string &;

    public:
        KmlFile(cstring filePath);
        ~KmlFile();

        //High level primitives
        void putKmlHeader();
        void putKmlFooter();
        
        void putLookAt(double longitude, double latitude, double altitude, AltitudeMode altitudeMode,
                double range, float tilt, float heading);

        void putPlaceMark(cstring name, cstring description, cstring styleUrl, 
                double longitude, double latitude, double altitude, AltitudeMode altitudeMode);

        void putGroundOverlay(cstring name, unsigned int altitude, AltitudeMode altitudeMode, 
                BoundingBox<double> bbox, double rotation, const ColorRGBA &color);
        void putGroundOverlay(cstring name, unsigned int altitude, AltitudeMode altitudeMode, 
                BoundingBox<double> bbox, double rotation, cstring iconPath);

        //Hight Level style primitives
        void startStyle(cstring styleId = std::string(""));

        void putIconStyle(ColorRGBA color, ColorMode colorMode, float scale, float heading, cstring iconHref, const HotSpot &hotSpot);
        void putLabelStyle(ColorRGBA color, ColorMode colorMode, float scale);
        void putLineStyle(ColorRGBA color, ColorMode colorMode, float width);
        void putPolyStyle(ColorRGBA color, ColorMode colorMode, bool fill, bool outline);

        void endStyle();
      
        //Low level primitives
        void startKml();
        
        void startDocument(cstring documentId = std::string(""));
        void startPlacemark(cstring placemarkId = std::string(""));
        void startGroundOverlay(cstring placemarkId = std::string(""));
        void startLookAt(cstring lookAtId = std::string(""));

        void startIconStyle(cstring styleId = std::string(""));
        void startLabelStyle(cstring styleId = std::string(""));
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
        void putFill(bool fill);
        void putOutline(bool outline);
        void putLongitude(double longitude);
        void putLatitude(double latitude);
        void putAltitude(double altitude);
        void putRange(double range);
        void putTilt(float tilt);
        void putHeading(float heading);
        void putScale(float scale);
        void putWidth(float width);
        void putCoordinate(double longitude, double latitude, double height);
        void putCoordinates(unsigned int count, double *longitude, double *latitude);
        void putCoordinates(unsigned int count, double *longitude, double *latitude, double *height);
        void putColor(ColorRGBA color);
        void putColorMode(ColorMode colorMode);
        void putAltitudeMode(AltitudeMode altitudeMode);
        void putHotspot(const HotSpot &hotspot);
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
        void endLabelStyle();
        void endIconStyle();

        void endLookAt();
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
