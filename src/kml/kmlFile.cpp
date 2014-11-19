
#include <iomanip>

#include "log.hpp"
#include "kmlFile.hpp"

KmlFile::KmlFile(cstring filePath):
indentLevel(0), filePath(filePath) {
    file.open(filePath);
	
    if(file.bad() || file.fail()) {
        log4cpp::log_console->errorStream() << "Error while opening file" << filePath << " !";
		exit(EXIT_FAILURE);
	}
}
        
KmlFile::~KmlFile() {
    file << kml.str();

    if(file.bad() || file.fail()) {
        log4cpp::log_console->errorStream() << "Something went wrong while writing file " << filePath << " !";
		exit(EXIT_FAILURE);
	}

   file.close(); 
}

        
unsigned int KmlFile::getCurrentIndentLevel() {
    return indentLevel;
}

void KmlFile::skipLine() {
    kml << newLine();
}

void KmlFile::jumpLines(unsigned int lineCount) {
    for (unsigned int i = 0; i < lineCount; i++) {
        kml << newLine();
    }
}
        

void  KmlFile::startKml() {
    kml << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << newLine();
    kml << "<kml xmlns=\"http://www.opengis.net/kml/2.2\"" << newLine();
    kml << "\t xmlns:gx=\"http://www.google.com/kml/ext/2.2\">" << newLineAndIndent();
}
void  KmlFile::endKml() {
    removeTab();
    kml << "</kml>";
}
        
void KmlFile::startDocument(cstring documentId) {
    if(stringIsEmpty(documentId))
        kml << "<Document>" << newLineAndIndent();
    else
        kml << "<Document id=\"" + documentId + "\">" << newLineAndIndent();
}
void KmlFile::endDocument() {
    removeTab();
    kml << "</Document>" << newLineAndDedent();
}

void  KmlFile::startPlacemark(cstring placemarkId) {
    if(stringIsEmpty(placemarkId))
        kml << "<Placemark>" << newLineAndIndent();
    else
        kml << "<Placemark id=\"" + placemarkId + "\">" << newLineAndIndent();
}
void  KmlFile::endPlacemark() {
    removeTab();
    kml << "</Placemark>" << newLineAndDedent();
}

void  KmlFile::startGroundOverlay(cstring groundOverlayId) {
    if(stringIsEmpty(groundOverlayId))
        kml << "<GroundOverlay>" << newLineAndIndent();
    else
        kml << "<GroundOverlay id=\"" + groundOverlayId + "\">" << newLineAndIndent();
}
void  KmlFile::endGroundOverlay() {
    removeTab();
    kml << "</GroundOverlay>" << newLineAndDedent();
}

void  KmlFile::startLookAt(cstring lookAtId) {
    if(stringIsEmpty(lookAtId))
        kml << "<LookAt>" << newLineAndIndent();
    else
        kml << "<LookAt id=\"" + lookAtId + "\">" << newLineAndIndent();
}
void  KmlFile::endLookAt() {
    removeTab();
    kml << "</LookAt>" << newLineAndDedent();
}

void  KmlFile::startStyle(cstring styleId) {
    if(stringIsEmpty(styleId))
        kml << "<Style>" << newLineAndIndent();
    else
        kml << "<Style id=\"" + styleId + "\">" << newLineAndIndent();
}
void  KmlFile::endStyle() {
    removeTab();
    kml << "</Style>" << newLineAndDedent();
}

void  KmlFile::startIconStyle(cstring iconStyleId) {
    if(stringIsEmpty(iconStyleId))
        kml << "<IconStyle>" << newLineAndIndent();
    else
        kml << "<IconStyle id=\"" + iconStyleId + "\">" << newLineAndIndent();
}
void  KmlFile::endIconStyle() {
    removeTab();
    kml << "</IconStyle>" << newLineAndDedent();
}

void  KmlFile::startLabelStyle(cstring labelStyleId) {
    if(stringIsEmpty(labelStyleId))
        kml << "<LabelStyle>" << newLineAndIndent();
    else
        kml << "<LabelStyle id=\"" + labelStyleId + "\">" << newLineAndIndent();
}
void  KmlFile::endLabelStyle() {
    removeTab();
    kml << "</LabelStyle>" << newLineAndDedent();
}

void  KmlFile::startLineStyle(cstring lineStyleId) {
    if(stringIsEmpty(lineStyleId))
        kml << "<LineStyle>" << newLineAndIndent();
    else
        kml << "<LineStyle id=\"" + lineStyleId + "\">" << newLineAndIndent();
}
void  KmlFile::endLineStyle() {
    removeTab();
    kml << "</LineStyle>" << newLineAndDedent();
}

void  KmlFile::startPolyStyle(cstring polyStyleId) {
    if(stringIsEmpty(polyStyleId))
        kml << "<PolyStyle>" << newLineAndIndent();
    else
        kml << "<PolyStyle id=\"" + polyStyleId + "\">" << newLineAndIndent();
}
void  KmlFile::endPolyStyle() {
    removeTab();
    kml << "</PolyStyle>" << newLineAndDedent();
}


void  KmlFile::startPoint() {
    kml << "<Point>" << newLineAndIndent();
}
void  KmlFile::endPoint() {
    removeTab();
    kml << "</Point>" << newLineAndDedent();
}

void  KmlFile::startLineString() {
    kml << "<LineString>" << newLineAndIndent();
}
void  KmlFile::endLineString() {
    removeTab();
    kml << "</LineString>" << newLineAndDedent();
}

void  KmlFile::startLinearRing() {
    kml << "<LinearRing>" << newLineAndIndent();
}
void  KmlFile::endLinearRing() {
    removeTab();
    kml << "</LinearRing>" << newLineAndDedent();
}

void  KmlFile::startPolygon() {
    kml << "<Polygon>" << newLineAndIndent();
}
void  KmlFile::endPolygon() {
    removeTab();
    kml << "</Polygon>" << newLineAndDedent();
}


void  KmlFile::putName(cstring name) {
    if(!stringIsEmpty(name))
        kml << "<name>"+name+"</name>"<<newLine();
}

void  KmlFile::putAuthor(cstring author) {
    if(!stringIsEmpty(author))
        kml << "<author>"+author+"</author>"<<newLine();
}

void  KmlFile::putDescription(cstring description) {
    if(!stringIsEmpty(description))
        kml << "<description>"+description+"</description>"<<newLine();
}
        
void KmlFile::putStyleUrl(cstring styleId) {
    if(!stringIsEmpty(styleId))
        kml << "<styleUrl>#" + styleId + "</styleUrl>"<<newLine();
}

void KmlFile::putIcon(cstring href) {
    if(!stringIsEmpty(href)) {
         kml << "<Icon>" << newLineAndIndent();
         kml << "<href>"+href+"</href>"<<newLine();
         removeTab();
         kml << "</Icon>" << newLineAndDedent();
    }
}

void  KmlFile::putVisibility(bool visible) {
    kml << "<visibility>"+(visible ? std::string("1") : std::string("0"))+"</visibility>"<<newLine();
}
        
void KmlFile::putExtrude(bool extrude) {
    kml << "<extrude>"+(extrude ? std::string("1") : std::string("0"))+"</extrude>"<<newLine();
}

void KmlFile::putTesselate(bool tesselate) {
    kml << "<tesselate>"+(tesselate ? std::string("1") : std::string("0"))+"</tesselate>"<<newLine();
}
        
void KmlFile::putOpen(bool open) {
    kml << "<open>"+(open ? std::string("1") : std::string("0"))+"</open>"<<newLine();
}

void KmlFile::putFill(bool fill) {
    kml << "<fill>"+(fill ? std::string("1") : std::string("0"))+"</fill>"<<newLine();
}

void KmlFile::putOutline(bool outline) {
    kml << "<outline>"+(outline ? std::string("1") : std::string("0"))+"</outline>"<<newLine();
}

void KmlFile::putWidth(float width) {
    kml << "<width>" << width << "</width>"<<newLine();
}

void KmlFile::putLongitude(double longitude) {
    kml << "<longitude>" << longitude << "</longitude>"<<newLine();
}
void KmlFile::putLatitude(double latitude) {
    kml << "<latitude>" << latitude << "</latitude>"<<newLine();
}
void KmlFile::putAltitude(double altitude) {
    kml << "<altitude>" << altitude << "</altitude>"<<newLine();
}
void KmlFile::putRange(double range) {
    kml << "<range>" << range << "</range>"<<newLine();
}
void putRange(double range);

void KmlFile::putTilt(float tilt) {
    kml << "<tilt>" << tilt << "</tilt>"<<newLine();
}
void KmlFile::putHeading(float heading) {
    kml << "<heading>" << heading << "</heading>"<<newLine();
}

void KmlFile::putScale(float scale) {
    kml << "<scale>" << scale << "</scale>"<<newLine();
}

void KmlFile::putColor(ColorRGBA color) {
    kml << "<color>" 
        << std::setfill('0') << std::setw(2) << std::hex << static_cast<unsigned int>(color.a)
        << std::setfill('0') << std::setw(2) << std::hex << static_cast<unsigned int>(color.b)
        << std::setfill('0') << std::setw(2) << std::hex << static_cast<unsigned int>(color.g)
        << std::setfill('0') << std::setw(2) << std::hex << static_cast<unsigned int>(color.r)
        << "</color>" 
        << newLine();
}

void KmlFile::putColorMode(ColorMode colorMode) {
    switch(colorMode) {
        case NORMAL:
            kml << "<colorMode>normal</colorMode>"<<newLine();
            break;
        case RANDOM:
            kml << "<colorMode>random</colorMode>"<<newLine();
            break;
    }
}

void KmlFile::putAltitudeMode(AltitudeMode altitudeMode) {
    switch(altitudeMode) {
        case CLAMP_TO_GROUND:
            kml << "<altitudeMode>clampToGround</altitudeMode>";
            break;
        case CLAMP_TO_SEA_FLOOR:
            kml << "<altitudeMode>clampToSeaFloor</altitudeMode>";
            break;
        case RELATIVE_TO_GROUND:
            kml << "<altitudeMode>relativeToGround</altitudeMode>";
            break;
        case RELATIVE_TO_SEA_FLOOR:
            kml << "<altitudeMode>relativeToSeaFloor</altitudeMode>";
            break;
        case ABSOLUTE:
            kml << "<altitudeMode>absolute</altitudeMode>";
            break;
    }
    kml << newLine();
}

void KmlFile::putHotspot(const HotSpot &hotSpot) {
    if(hotSpot.ux != NONE) {
        kml << "<hotSpot "
            <<    "x=\"" << hotSpot.strX() 
            << "\" y=\"" << hotSpot.strY() 
            << "\" xunits=\"" << hotSpot.strUX() 
            << "\" yunits=\"" << hotSpot.strUY()
            << "\"/>" << newLine();
    }
}
        
void KmlFile::putDate(const std::tm &date, DateFormat dateFormat) {
    kml << "<date>" << dateToString(date, dateFormat) << "</date>" << newLine();
}
        
void KmlFile::putTimeStamp(const std::tm &date, DateFormat dateFormat, cstring timeStampId) {
    if(stringIsEmpty(timeStampId))
        kml << "<TimeStamp>" << newLineAndIndent();
    else
        kml << "<TimeStamp id=\"" << timeStampId << "\">" << newLineAndIndent();
    kml << "<when>" << dateToString(date, dateFormat) << "</when>" << newLine();
    removeTab();
    kml << "</TimeStamp>" << newLineAndDedent();
}
void KmlFile::putTimeSpan(const std::tm &beginDate, const std::tm &endDate, DateFormat dateFormat, cstring timeSpanId) {
}
        
void KmlFile::putCoordinate(double longitude, double latitude, double altitude) {
    kml<< "<coordinates>" << longitude << "," << latitude << "," << altitude << "</coordinates>" << newLine();
}

void KmlFile::putCoordinates(unsigned int count, double *longitude, double *latitude) {
    kml << "<coordinates>"<<newLineAndIndent();
    for (unsigned int i = 0; i < count; i++) {
        kml<< longitude << "," << latitude << "," << 0.0f << newLine();
    }
    removeTab();
    kml << "<coordinates>"<<newLineAndDedent();
}

void KmlFile::putCoordinates(unsigned int count, double *longitude, double *latitude, double *altitude) {
    kml << "<coordinates>"<<newLineAndIndent();
    for (unsigned int i = 0; i < count; i++) {
        kml<< longitude << "," << latitude << "," << altitude << newLine();
    }
    removeTab();
    kml << "<coordinates>"<<newLineAndDedent();
}
        
void KmlFile::putLatLonBox(BoundingBox<double> bbox, double rotation) {
    kml << "<LatLonBox>" << newLineAndIndent();
    kml << "<north>" << bbox.ymax << "</north>" << newLine();
    kml << "<south>" << bbox.ymin << "</south>" << newLine();
    kml << "<east>" << bbox.xmin << "</east>" << newLine();
    kml << "<west>" << bbox.xmax << "</west>" << newLine();
    kml << "<rotation>" << rotation << "</rotation>" << newLine();
    removeTab();
    kml << "</LatLonBox>" << newLineAndDedent();
}


// Tablulation and newline management
void KmlFile::removeTab() {
    kml.seekp(std::streamoff(-1)+ kml.tellp());
}

const std::string KmlFile::newLineAndDedent() {
    indentLevel--;
    return newLine();
}

const std::string KmlFile::newLine() {
    std::stringstream ss;
    ss << '\n';
    for (unsigned int i = 0; i < indentLevel; i++) {
        ss << '\t';
    }
    return ss.str();
}

const std::string KmlFile::newLineAndIndent() {
    indentLevel++;
    return newLine();
}
        
bool KmlFile::stringIsEmpty(cstring string) {
    return string.compare("") == 0;
}
        
std::string KmlFile::dateToString(const std::tm &date, DateFormat format) {
    
    char buffer[80];
    switch(format) {
        case YYYY:
            strftime(buffer,80,"%Y",&date);
            break;
        case YYYY_MM:
            strftime(buffer,80,"%Y-%m",&date);
            break;
        case YYYY_MM_DD:
            strftime(buffer,80,"%Y-%m-%d",&date);
            break;
        case YYYY_MM_DD_hh_mm_ss:
            strftime(buffer,80,"%Y-%m-%dT%I:%M:%SZ",&date);
            break;
        case YYYY_MM_DD_hh_mm_ss_zzzzzz:
            strftime(buffer,80,"%Y-%m-%dT%I:%M:%S+00:00",&date);
            break;
    }

    return std::string(buffer);
}
        
void KmlFile::putKmlHeader() {
    time_t t = time(0);
    std::tm *now = localtime(&t);

    startKml();
    startDocument("Root");
    putName("Environemental contaminant viewer");
    putDescription("This file was generated automatically with real meteorological data and is part of the Ensimag visualization project.");
    putDate(*now, YYYY_MM_DD_hh_mm_ss);
    putAuthor("Jean-Baptiste Keck");
    putAuthor("Alexandre Ribard");
    skipLine();
    putVisibility(true);
    putOpen(false);
    skipLine();
}

void KmlFile::putKmlFooter() {
    endDocument();
    endKml();
}
        
void KmlFile::putGroundOverlay(cstring name, unsigned int altitude, AltitudeMode altitudeMode, 
                BoundingBox<double> bbox, double rotation, const ColorRGBA &color) {
    startGroundOverlay();
    putName(name);
    putAltitude(altitude);
    putAltitudeMode(altitudeMode);
    putLatLonBox(bbox);
    putColor(color);
    endGroundOverlay();
}
        
void KmlFile::putGroundOverlay(cstring name, unsigned int altitude, AltitudeMode altitudeMode, 
        BoundingBox<double> bbox, double rotation, cstring iconPath) {
    startGroundOverlay();
    putName(name);
    putAltitude(altitude);
    putAltitudeMode(altitudeMode);
    putLatLonBox(bbox);
    putIcon(iconPath);
    endGroundOverlay();
}
        
void KmlFile::putPlaceMark(cstring name, cstring description, cstring styleUrl, 
        double longitude, double latitude, double altitude, AltitudeMode altitudeMode) {
    startPlacemark();
    putName(name);
    putDescription(description);
    putStyleUrl(styleUrl);
    putAltitudeMode(altitudeMode);
    startPoint();
    putCoordinate(longitude, latitude, altitude);
    endPoint();
    endPlacemark();
}

void KmlFile::putLookAt(double longitude, double latitude, double altitude, AltitudeMode altitudeMode,
                double range, float tilt, float heading) {
        startLookAt();
        putLongitude(longitude);
        putLatitude(latitude);
        putAltitude(altitude);
        putAltitudeMode(altitudeMode);
        putRange(range);
        putTilt(tilt);
        putHeading(heading);
        endLookAt();
}

void KmlFile::putIconStyle(ColorRGBA color, ColorMode colorMode, float scale, float heading) {
    startIconStyle();
    putColor(color);
    putColorMode(colorMode);
    putScale(scale);
    putHeading(heading);
    endIconStyle();
}

void KmlFile::putIconStyle(cstring iconHref, const HotSpot &hotSpot, float scale, float heading) {
    startIconStyle();
    putIcon(iconHref);
    putHotspot(hotSpot);
    putScale(scale);
    putHeading(heading);
    endIconStyle();
}

void KmlFile::putLabelStyle(ColorRGBA color, ColorMode colorMode, float scale) {
    startLabelStyle();
    putColor(color);
    putColorMode(colorMode);
    putScale(scale);
    endLabelStyle();
}

void KmlFile::putLineStyle(ColorRGBA color, ColorMode colorMode, float width) {
    startLineStyle();
    putColor(color);
    putColorMode(colorMode);
    putWidth(width);
    endLineStyle();
}

void KmlFile::putPolyStyle(ColorRGBA color, ColorMode colorMode, bool fill, bool outline) {
    startPolyStyle();
    putColor(color);
    putColorMode(colorMode);
    putFill(fill);
    putOutline(outline);
    endPolyStyle();
}

