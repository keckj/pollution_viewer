#ifndef KMLUTILS_H
#define KMLUTILS_H

#include <string>
#include <sstream>

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

enum OffsetType {
    HOTSPOT,
    SIZE,
    OVERLAY_XY,
    SCREEN_XY,
    ROTATION_XY
};

enum OffsetUnit {
    NONE,
    PIXELS,
    INSET_PIXELS,
    FRACTION
};

union OffsetValue {
    int i;
    float f;
    OffsetValue(float f) : f(f) {}
    OffsetValue(int i) : i(i) {}
};

struct Offset {
    OffsetValue x, y;
    OffsetUnit ux, uy;

    Offset() : x(0), y(0), ux(NONE), uy(NONE) {}
    explicit Offset(float x, float y) : x(x), y(y), ux(FRACTION), uy(FRACTION) {}
    explicit Offset(int x, OffsetUnit ux, float y) : x(x), y(y), ux(ux), uy(FRACTION) {}
    explicit Offset(float x, int y, OffsetUnit uy) : x(x), y(y), ux(FRACTION), uy(uy) {}
    explicit Offset(int x, OffsetUnit ux, int y, OffsetUnit uy) : x(x), y(y), ux(ux), uy(uy) {}
    
    static const std::string strUnit(OffsetUnit unit) {
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

#endif /* end of include guard: KMLUTILS_H */
