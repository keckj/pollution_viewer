
#include <stdexcept>
#include "stationType.hpp"

StationType::StationType() : _type() {
}

StationType::StationType(const StationType &st) : _type(st._type) {
}

StationType::StationType(const std::string &type) {
    if (type.compare("Urbain") == 0) 
        _type = URBAIN;
    else if (type.compare("Périurbain") == 0) 
        _type = PERIURBAIN;
    else if (type.compare("Rurale") == 0) 
        _type = RURALE;
    else if (type.compare("Trafic") == 0) 
        _type = TRAFIC;
    else if (type.compare("Industrielle") == 0) 
        _type = INDUSTRIELLE;
    else
        throw new std::runtime_error("Unknown station type: " + type);
}

StationType& StationType::operator= (const StationType &st) {
    this->_type = st._type;
    return *this;
}

StationType& StationType::operator= (const std::string &type) {
    StationType st(type);
    this->_type = st._type;
    return *this;
}

const std::string StationType::toString() const {
    switch(_type) {
        case URBAIN: return "Urbain";
        case PERIURBAIN: return "Périurbain";
        case RURALE: return "Rurale";
        case TRAFIC: return "Trafic";
        case INDUSTRIELLE: return "Industrielle";
    }

    return "";
}

std::ostream & operator<< (std::ostream &os, const StationType &st) {
    os << st.toString();
    return os;
}
