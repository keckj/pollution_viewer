#ifndef SEARCHBORDER_H
#define SEARCHBORDER_H

#include <iterator>
#include "lines.hpp"
#include "interpolator.hpp"
#include "lines.hpp"
#include "isoline.hpp"
#include "isocontour.hpp"

enum RotationDirection {
    CLOCKWISE=0,
    COUNTER_CLOCKWISE
};

enum SearchSide {
    TOP=0,
    LEFT,
    BOTTOM,
    RIGHT
};

enum SearchDir {
    TOP_WEST=0,
    LEFT_SOUTH,
    BOTTOM_EAST,
    RIGHT_NORTH,
    TOP_EAST,
    RIGHT_SOUTH,
    BOTTOM_WEST,
    LEFT_NORTH
};


enum ListPos {
    FRONT,
    BACK
};

template <typename T>
struct MatchedLine {
    Line<T> *line;
    ListPos pos;

    MatchedLine() : line(0), pos(FRONT) {}
    MatchedLine(Line<T>* line, ListPos pos) : line(line), pos(pos) {}
};

template <typename T>
struct SearchBorder {
    Axe axe;
    RotationDirection rotationDir;
    SearchSide side;
    SearchDir dir;

    Vec<T> v;
    const BoundingBox<T> bbox;

    std::list<MatchedLine<T>> matchedLines;

    template <typename F>
        SearchBorder(const Vec<T> &v, const BoundingBox<T> &bbox, double isovalue, const InterpolatedData<F> &data);

    void match(Line<T> *line);
    MatchedLine<T> extractBestMatch();

    void operator++(int i);
};

template <typename T>
template <typename F>
SearchBorder<T>::SearchBorder(const Vec<T> &v, const BoundingBox<T> &bbox, double isovalue, const InterpolatedData<F> &data):
    v(v), bbox(bbox)
{
    using Utils::areEqual;

    double d1, d2;
    unsigned int ix = static_cast<unsigned int>((v.x - bbox.xmin)/(bbox.xmax - bbox.xmin) * (data.gridWidth - 1u));
    unsigned int iy = static_cast<unsigned int>((bbox.ymax - v.y)/(bbox.ymax - bbox.ymin) * (data.gridHeight - 1u));

    d1 = static_cast<double>(data.density[iy*data.gridWidth+ix]);

    if(areEqual<T>(v.x, bbox.xmin)) {
        axe = AXE_Y;
        side = LEFT;
    }
    else if(areEqual<T>(v.x, bbox.xmax)) {
        axe = AXE_Y;
        side = RIGHT;
    }
    else if(areEqual<T>(v.y, bbox.ymin)) {
        axe = AXE_X;
        side = BOTTOM;
    }
    else if(areEqual<T>(v.y, bbox.ymax)) {
        axe = AXE_X;
        side = TOP;
    }
    else {
        assert(false);
    }

    unsigned int i = 1u;
    do {
        if(axe == AXE_X) {
            if(ix + i == data.gridWidth) {
                break;
            }
            d2 = static_cast<double>(data.density[iy*data.gridWidth+ix+i++]);
        }
        else {
            if(iy + i == data.gridHeight) {
                break;
            }
            d2 = static_cast<double>(data.density[(iy+i++)*data.gridWidth+ix]);
        }
    } while(!((d1 <= isovalue && d2 > isovalue) || (d1 > isovalue && d2 <= isovalue))); 

    if(d1 < isovalue) {
        switch(side) {
            case TOP: rotationDir=COUNTER_CLOCKWISE; dir=TOP_WEST; break;
            case LEFT: rotationDir=COUNTER_CLOCKWISE; dir=LEFT_SOUTH; break;
            case BOTTOM: rotationDir=CLOCKWISE; dir=BOTTOM_WEST; break;
            case RIGHT: rotationDir=CLOCKWISE; dir=RIGHT_SOUTH; break;
        }
    }
    else if (d1 > isovalue) {
        switch(side) {
            case TOP: rotationDir=CLOCKWISE; dir=TOP_EAST; break;
            case LEFT: rotationDir=CLOCKWISE; dir=LEFT_NORTH; break;
            case BOTTOM: rotationDir=COUNTER_CLOCKWISE; dir=BOTTOM_EAST; break;
            case RIGHT: rotationDir=COUNTER_CLOCKWISE; dir=RIGHT_NORTH; break;
        }
    }
    else {
        assert(false);
    }
}

template <typename T>
void SearchBorder<T>::match(Line<T> *line) {
    using Utils::areEqual;
    switch(side) {
        case TOP: 
            if(areEqual<double>(line->front().y, bbox.ymax)) {
                if ((dir == TOP_WEST && line->front().x < v.x) || (dir == TOP_EAST && line->front().x > v.x))
                    matchedLines.push_back(MatchedLine<T>(line, FRONT));

            }
            else if(areEqual<double>(line->back().y, bbox.ymax)) {
                if ((dir == TOP_WEST && line->back().x < v.x) || (dir == TOP_EAST && line->back().x > v.x))
                    matchedLines.push_back(MatchedLine<T>(line, BACK));
            }
            break;
        case LEFT:
            if(areEqual<double>(line->front().x, bbox.xmin)) {
                if((dir == LEFT_NORTH && line->front().y > v.y) || (dir == LEFT_SOUTH && line->front().y < v.y))
                    matchedLines.push_back(MatchedLine<T>(line,FRONT));
            }
            else if(areEqual<double>(line->back().x, bbox.xmin)) {
                if((dir == LEFT_NORTH && line->back().y > v.y) || (dir == LEFT_SOUTH && line->back().y < v.y))
                    matchedLines.push_back(MatchedLine<T>(line,BACK));
            }
            break;
        case BOTTOM:
            if(areEqual<double>(line->front().y, bbox.ymin)) {
                if((dir == BOTTOM_WEST && line->front().x < v.x) || (dir == BOTTOM_EAST && line->front().x > v.x))
                    matchedLines.push_back(MatchedLine<T>(line,FRONT));
            }
            else if(areEqual<double>(line->back().y, bbox.ymin)) {
                if((dir == BOTTOM_WEST && line->back().x < v.x) || (dir == BOTTOM_EAST && line->back().x > v.x))
                    matchedLines.push_back(MatchedLine<T>(line,BACK));
            }
            break;
        case RIGHT:
            if(areEqual<double>(line->front().x, bbox.xmax)) {
                if((dir == RIGHT_NORTH && line->front().y > v.y) || (dir == RIGHT_SOUTH && line->front().y < v.y))
                    matchedLines.push_back(MatchedLine<T>(line,FRONT));
            }
            else if(areEqual<double>(line->back().x, bbox.xmax)) {
                if((dir == RIGHT_NORTH && line->back().y > v.y) || (dir == RIGHT_SOUTH && line->back().y < v.y))
                    matchedLines.push_back(MatchedLine<T>(line,BACK));
            }
            break;
    }
}

template <typename T>
MatchedLine<T> SearchBorder<T>::extractBestMatch() {
    Vec<T> mask;
    if(axe == AXE_X)
        mask = Vec<T>(1,0,0);
    else
        mask = Vec<T>(0,1,0);

    if(matchedLines.empty())
        return MatchedLine<T>(0,FRONT);

    T d2min = std::numeric_limits<T>::max();
    MatchedLine<T> bestMatch;

    for (MatchedLine<T> &ml : matchedLines) {
        Vec<T> mlPoint = (ml.pos == FRONT ? ml.line->front() : ml.line->back());
        T d2 = ((v - mlPoint)*mask).squaredNorm();
        if(d2 < d2min) {
            bestMatch = ml;
            d2min = d2;
        }

    }

    return bestMatch;
}

template <typename T>
void SearchBorder<T>::operator++(int i) {
    axe = (axe == AXE_X ? AXE_Y : AXE_X);

    if(rotationDir == CLOCKWISE) {
        switch(side) {
            case TOP: side = RIGHT;break;
            case RIGHT: side = BOTTOM; break;
            case BOTTOM: side = LEFT; break;
            case LEFT: side = TOP; break;
        }
    }
    else {
        switch(side) {
            case TOP: side = LEFT; break;
            case LEFT: side = BOTTOM; break;
            case BOTTOM: side = RIGHT; break;
            case RIGHT: side = TOP; break;
        }
    }

    if(rotationDir == CLOCKWISE) {
        switch(dir) {
            case TOP_EAST: dir = RIGHT_SOUTH; v = bbox.topRight(); break;
            case RIGHT_SOUTH: dir = BOTTOM_WEST; v = bbox.bottomRight(); break;
            case BOTTOM_WEST: dir = LEFT_NORTH; v = bbox.bottomLeft(); break;
            case LEFT_NORTH: dir = TOP_EAST; v = bbox.topLeft(); break;
            default: assert(false);
        }
    }
    else {
        switch(dir) {
            case TOP_WEST: dir = LEFT_SOUTH; v = bbox.topLeft(); break;
            case LEFT_SOUTH: dir = BOTTOM_EAST; v = bbox.bottomLeft(); break;
            case BOTTOM_EAST: dir = RIGHT_NORTH; v = bbox.bottomRight(); break;
            case RIGHT_NORTH: dir = TOP_WEST; v = bbox.topRight(); break;
            default: assert(false);
        }
    }
}

template <typename T>
std::ostream & operator<<(std::ostream &os, const SearchBorder<T> &sb) {
    os << "[SearchBorder]";
    os << "\n\tAxe: ";
    switch(sb.axe) {
        case(AXE_X): os << "AXE_X"; break;
        case(AXE_Y): os << "AXE_Y"; break;
        case(AXE_Z): os << "AXE_Z"; break;
    }
    os << "\n\tRotationDir: ";
    switch(sb.rotationDir) {
        case(CLOCKWISE):         os << "CLOCKWISE"; break;
        case(COUNTER_CLOCKWISE): os << "COUNTER_CLOCKWISE"; break;
    }
    os << "\n\tSide: ";
    switch(sb.side) {
        case(TOP):    os << "TOP"; break;
        case(LEFT):   os << "LEFT"; break;
        case(BOTTOM): os << "BOTTOM"; break;
        case(RIGHT):  os << "RIGHT"; break;
    }
    os << "\n\tDir: ";
    switch(sb.dir) {
        case(TOP_WEST):    os << "TOP_WEST"; break;
        case(LEFT_SOUTH):  os << "LEFT_SOUTH"; break;
        case(BOTTOM_EAST): os << "BOTTOM_EAST"; break;
        case(RIGHT_NORTH): os << "RIGHT_NORTH"; break;
        case(TOP_EAST):    os << "TOP_EAST"; break;
        case(RIGHT_SOUTH): os << "RIGHT_SOUTH"; break;
        case(BOTTOM_WEST): os << "BOTTOM_WEST"; break;
        case(LEFT_NORTH):  os << "LEFT_NORTH"; break;
    }

    os << std::endl;

    return os;
}

#endif /* end of include guard: SEARCHBORDER_H */
