
#include <iomanip>

#include "log.hpp"
#include "kmlFile.hpp"

KmlFile::KmlFile(std::string filePath):
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
    kml << "<Style>" << newLineAndIndent();
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



void  KmlFile::putName(cstring name) {
    kml << "<name>"+name+"</name>"<<newLine();
}

void  KmlFile::putVisibility(bool visible) {
    kml << "<visibility>"+(visible ? std::string("1") : std::string("0"))+"</visibility>"<<newLine();
}

void  KmlFile::putDescription(cstring description) {
    kml << "<description>"+description+"</description>"<<newLine();
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
        
void KmlFile::putCoordinate(float longitude, float latitude, float altitude) {
    kml<< "<coordinates>" << longitude << "," << latitude << "," << altitude << "</coordinates>" << newLine();
}

void KmlFile::putCoordinates(unsigned int count, float *longitude, float *latitude, float *altitude) {
    kml << "<coordinates>"<<newLineAndIndent();
    for (unsigned int i = 0; i < count; i++) {
        kml<< longitude << "," << latitude << "," << altitude << newLine();
    }
    removeTab();
    kml << "<coordinates>"<<newLineAndDedent();
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

void KmlFile::removeTab() {
    kml.seekp(std::streamoff(-1)+ kml.tellp());
}
