
#ifndef KMLFILE_H
#define KMLFILE_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>

#include "colors.hpp"
#include "coords.hpp"
#include "kmlUtils.hpp"
#include "isolineUtils.hpp"
#include "lines.hpp"

class KmlFile {

    using cstring = const std::string &;

    public:
        KmlFile(cstring filePath);
        virtual ~KmlFile();

        // USEFULL FUNCTIONS //
        void skipLine();
        void jumpLines(unsigned int lineCount);
        unsigned int getCurrentIndentLevel();

        // HIGH LEVEL PRIMITIVES //

        void putComment(cstring comment);

        void putFolder(cstring name, cstring description, bool open, bool visibility);
        
        void putLookAt(double longitude, double latitude, double altitude, AltitudeMode altitudeMode,
                double range, float tilt, float heading);

        void putPlaceMark(cstring name, cstring description, cstring styleUrl, 
                double longitude, double latitude, double altitude, AltitudeMode altitudeMode);

        void putLineString(cstring name, cstring description,
                const Line<double> &line,
                cstring styleUrl = std::string(""),
                AltitudeMode AltitudeMode = CLAMP_TO_GROUND,
                unsigned int drawOrder=0u, bool extrude=false, bool tesselate=false);
        
        void putLineStrings(cstring name, cstring description,
                const MultiLine<double> &lines,
                cstring styleUrl = std::string(""),
                AltitudeMode AltitudeMode = CLAMP_TO_GROUND,
                unsigned int drawOrder=0u, bool extrude=false, bool tesselate=false);
        
        void putColorLineString(cstring name, cstring description,
                cstring styleUrlPrefix,
                const ColorLine<double,4u> &colorLine,
                AltitudeMode AltitudeMode = CLAMP_TO_GROUND,
                unsigned int drawOrder=0u, bool extrude=false, bool tesselate=false);
        
        void putColorLineStrings(cstring name, cstring description,
                cstring styleUrlPrefix,
                const ColorMultiLine<double,4u> &colorLines,
                bool visibility, const std::tm &date,
                AltitudeMode AltitudeMode = CLAMP_TO_GROUND,
                unsigned int drawOrder=0u, bool extrude=false, bool tesselate=false);

        void putPolygon(cstring name, cstring description, 
                const Line<double> &outerBoundary, 
                cstring styleUrl = std::string(""),
                AltitudeMode altitudeMode = CLAMP_TO_GROUND,
                unsigned int drawOrder = 0u, bool extrude=false, bool tesselate=false);

        void putColorPolygons(cstring name, cstring description, 
                cstring styleUrlPrefix,
                const ColorMultiLine<double,4u> &outerBoundaries, 
                bool visibility, const std::tm &date,
                AltitudeMode altitudeMode = CLAMP_TO_GROUND,
                unsigned int drawOrder = 0u, bool extrude=false, bool tesselate=false);

        void putGroundOverlay(cstring name, unsigned int altitude, AltitudeMode altitudeMode, 
                BoundingBox<double> bbox, double rotation, const Color<4u> &color);
        void putGroundOverlay(cstring name, unsigned int altitude, AltitudeMode altitudeMode, 
                BoundingBox<double> bbox, double rotation, cstring iconPath, bool visibility, const std::tm &date);
        
        void putScreenOverlay(cstring name, cstring description,
                const Offset &overlayXY, const Offset &screenXY, 
                const Offset &size, const Offset &rotationXY,
                float rotation, unsigned int drawOrder,
                cstring iconPath,
                bool visibility,
                const std::tm &date);

        // HIGH LEVEL STYLE PRIMITIVES //
        void startStyle(cstring styleId = std::string(""));

        void putIconStyle(const Color<4u> &color, ColorMode colorMode, float scale, float heading);
        void putIconStyle(cstring iconHref, const Offset &hotSpot, float scale, float heading);
        void putLabelStyle(const Color<4u> &color, ColorMode colorMode, float scale);
        void putLineStyle(const Color<4u> &color, ColorMode colorMode, float width);
        void putPolyStyle(const Color<4u> &color, ColorMode colorMode, bool fill, bool outline);

        void endStyle();
     

        // LOW LEVEL PRIMITIVES //
        void startKml();
        
        void startDocument(cstring documentId = std::string(""));
        void startFolder(cstring folderId = std::string(""));
        void startPlacemark(cstring placemarkId = std::string(""));
        void startMultiGeometry(cstring placemarkId = std::string(""));
        void startGroundOverlay(cstring placemarkId = std::string(""));
        void startScreenOverlay(cstring placemarkId = std::string(""));
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
        void putDrawOrder(unsigned int drawOrder);
        void putLongitude(double longitude);
        void putLatitude(double latitude);
        void putAltitude(double altitude);
        void putRange(double range);
        void putRotation(float rotation);
        void putTilt(float tilt);
        void putHeading(float heading);
        void putScale(float scale);
        void putWidth(float width);
        void putCoordinate(double longitude, double latitude, double height);
        void putCoordinates(unsigned int count, double *longitude, double *latitude);
        void putCoordinates(unsigned int count, double *longitude, double *latitude, double *height);
        void putCoordinates(const Line<double> &line);
        void putOuterBoundary(const Line<double> &line);
        void putColor(const Color<4u> &color);
        void putColorMode(ColorMode colorMode);
        void putAltitudeMode(AltitudeMode altitudeMode);
        void putOffset(const Offset &offset, OffsetType offsetType);
        void putHotspot(const Offset &hotspot);
        void putOverlayXY(const Offset &overlayXY);
        void putScreenXY(const Offset &screenXY);
        void putRotationXY(const Offset &rotationXY);
        void putSize(const Offset &size);
        void putDate(const std::tm &date, DateFormat dateFormat);
        void putTimeStamp(const std::tm &date, DateFormat dateFormat=YYYY_MM_DD_hh_mm_ss, cstring timeStampId = std::string(""));
        void putTimeSpan(const std::tm &beginDate, const std::tm &endDate, DateFormat dateFormat=YYYY_MM_DD_hh_mm_ss, cstring timeSpanId = std::string(""));
        void putLatLonBox(const BoundingBox<double> &bbox, double rotation = 0.0);

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
        void endMultiGeometry();
        void endGroundOverlay();
        void endScreenOverlay();
        void endFolder();
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
