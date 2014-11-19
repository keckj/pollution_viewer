
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
    kml << "<name>"+name+"</name>"<<newLine();
}

void  KmlFile::putAuthor(cstring author) {
    kml << "<author>"+author+"</author>"<<newLine();
}

void  KmlFile::putDescription(cstring description) {
    kml << "<description>"+description+"</description>"<<newLine();
}
        
void KmlFile::putStyleUrl(cstring styleId) {
    kml << "<styleUrl>#" + styleId + "</styleUrl>"<<newLine();
}

void KmlFile::putIcon(cstring href) {
         kml << "<Icon>" << newLineAndIndent();
         kml << "<href>"+href+"</href>"<<newLine();
         removeTab();
         kml << "</Icon>" << newLineAndDedent();
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
        
void KmlFile::putWidth(unsigned int width) {
    kml << "<width>" << width << "</width>"<<newLine();
}

void KmlFile::putAltitude(unsigned int altitude) {
    kml << "<altitude>" << altitude << "</altitude>"<<newLine();
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
        
void KmlFile::putCoordinate(float longitude, float latitude, float altitude) {
    kml<< "<coordinates>" << longitude << "," << latitude << "," << altitude << "</coordinates>" << newLine();
}

void KmlFile::putCoordinates(unsigned int count, float *longitude, float *latitude) {
    kml << "<coordinates>"<<newLineAndIndent();
    for (unsigned int i = 0; i < count; i++) {
        kml<< longitude << "," << latitude << "," << 0.0f << newLine();
    }
    removeTab();
    kml << "<coordinates>"<<newLineAndDedent();
}

void KmlFile::putCoordinates(unsigned int count, float *longitude, float *latitude, float *altitude) {
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
        
void KmlFile::skipLine() {
    kml << newLine();
}

void KmlFile::jumpLines(unsigned int lineCount) {
    for (unsigned int i = 0; i < lineCount; i++) {
        kml << newLine();
    }
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
        
void KmlFile::putGroundOverlay(cstring name, unsigned int altitude, AltitudeMode altitudeMode, BoundingBox<double> bbox, double rotation, cstring iconPath) {
    startGroundOverlay();
    putName(name);
    putAltitude(altitude);
    putAltitudeMode(altitudeMode);
    putLatLonBox(bbox);
    putIcon(iconPath);
    endGroundOverlay();
}
