

#ifndef KMLFILE_H
#define KMLFILE_H

#include <iostream>
#include <sstream>
#include <fstream>

#include "colors.hpp"
#include "coords.hpp"
#include "kmlUtils.hpp"

class KmlFile {

    using cstring = const std::string &;

    public:
        KmlFile(cstring filePath);
        ~KmlFile();

        // USEFULL FUNCTIONS //
        void skipLine();
        void jumpLines(unsigned int lineCount);
        unsigned int getCurrentIndentLevel();

        // HIGH LEVEL PRIMITIVES //
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

        // HIGH LEVEL STYLE PRIMITIVES //
        void startStyle(cstring styleId = std::string(""));

        void putIconStyle(ColorRGBA color, ColorMode colorMode, float scale, float heading);
        void putIconStyle(cstring iconHref, const HotSpot &hotSpot, float scale, float heading);
        void putLabelStyle(ColorRGBA color, ColorMode colorMode, float scale);
        void putLineStyle(ColorRGBA color, ColorMode colorMode, float width);
        void putPolyStyle(ColorRGBA color, ColorMode colorMode, bool fill, bool outline);

        void endStyle();
     

        // LOW LEVEL PRIMITIVES //
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
        
    private:
        unsigned int indentLevel;
        std::string filePath;
        
        std::ofstream file;
        std::stringstream kml;
       
        // HELPER FUNTIONS //
        bool stringIsEmpty(cstring string);
        void removeTab();
        const std::string newLineAndIndent();
        const std::string newLine();
        const std::string newLineAndDedent();
        std::string dateToString(const std::tm &date, DateFormat format);
};


#endif /* end of include guard: KMLFILE_H */
