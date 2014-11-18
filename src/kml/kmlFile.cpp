
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
    kml << "<kml xmlns=\"http://www.opengis.net/kml/2.2\">" << newLineAndIndent();
}
void  KmlFile::endKml() {
    removeTab();
    kml << "</kml>";
}
        
void KmlFile::startDocument() {
    kml << "<Document>" << newLineAndIndent();
}
void KmlFile::endDocument() {
    removeTab();
    kml << "</Document>" << newLineAndDedent();
}

void  KmlFile::startPlacemark() {
    kml << "<Placemark>" << newLineAndIndent();
}
void  KmlFile::endPlacemark() {
    removeTab();
    kml << "</Placemark>" << newLineAndDedent();
}

void  KmlFile::startStyle(cstring styleId) {
    if(styleId.compare("") == 0)
        kml << "<Style>" << newLineAndIndent();
    else
        kml << "<Style id=\"" + styleId + "\">" << newLineAndIndent();
}
void  KmlFile::endStyle() {
    removeTab();
    kml << "</Style>" << newLineAndDedent();
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

void  KmlFile::startIconStyle() {
    kml << "<IconStyle>" << newLineAndIndent();
}
void  KmlFile::endIconStyle() {
    removeTab();
    kml << "</IconStyle>" << newLineAndDedent();
}

void  KmlFile::startLineStyle() {
    kml << "<LineStyle>" << newLineAndIndent();
}
void  KmlFile::endLineStyle() {
    removeTab();
    kml << "</LineStyle>" << newLineAndDedent();
}

void  KmlFile::startPolyStyle() {
    kml << "<PolyStyle>" << newLineAndIndent();
}
void  KmlFile::endPolyStyle() {
    removeTab();
    kml << "</PolyStyle>" << newLineAndDedent();
}


void  KmlFile::putName(cstring name) {
    kml << "<name>"+name+"</name>"<<newLine();
}

void  KmlFile::putDescription(cstring description) {
    kml << "<description>"+description+"</description>"<<newLine();
}
        
void KmlFile::putStyleUrl(cstring styleId) {
    kml << "<styleUrl>#" + styleId + "</styleUrl>"<<newLine();
}

void KmlFile::putIcon(cstring href) {
         kml << "<Icon>" << newLineAndIndent();
         kml << "<href>"+href+"</href>";
         removeTab();
         kml << "</Icon>" << newLineAndDedent();
}

void  KmlFile::putVisibility(bool visible) {
    kml << "<visibility>"+(visible ? std::string("1") : std::string("0"))+"</visibility>"<<newLine();
}
        
void putExtrude(bool extrude) {
    kml << "<extrude>"+(extrude ? std::string("1") : std::string("0"))+"</extrude>"<<newLine();
}

void putTesselate(bool tesselate) {
    kml << "<tesselate>"+(tesselate ? std::string("1") : std::string("0"))+"</tesselate>"<<newLine();
}
        
void putWidth(unsigned int width) {
    kml << "<width>"+width+"</width>"<<newLine();
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
        
void KmlFile::putLatLonBox(BoundingBox<float> bbox, float rotation) {
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
