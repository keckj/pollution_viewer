#ifndef ISOCONTOUR_H
#define ISOCONTOUR_H

#include "isoline.hpp"
#include "searchBorder.hpp"

template <typename T, unsigned int N, typename F>
struct IsoContour {
    MultiLine<T> lines;
    Color<N> color;
    
    F lowerValue;
    F upperValue;

    IsoContour(const IsoLine<T,N,F> &isolineLowVal, const IsoLine<T,N,F> &isolineHighVal, 
        const InterpolatedData<F> &data, const BoundingBox<double> &bbox);
};

template <typename T, unsigned int N, typename F>
using IsoContourList = std::list<IsoContour<T,N,F>>;

//Make isocontours from isolines
template <typename T, unsigned int N, typename F>
IsoContour<T,N,F>::IsoContour(const IsoLine<T,N,F> &isolineLowVal, const IsoLine<T,N,F> &isolineHighVal, 
        const InterpolatedData<F> &data, const BoundingBox<double> &bbox) :
    lines(), color(isolineLowVal.lines.color), 
    lowerValue(isolineLowVal.value), upperValue(isolineHighVal.value) {

        using Utils::areEqual;

        const IsoLine<T,N,F> &isoline = isolineLowVal;

        MultiLine<T> mlines(isoline.lines.lines);

        while(!mlines.empty()) {
            Line<T> buffer;
            buffer.splice(buffer.begin(), mlines.front());
            mlines.pop_front();

            if(buffer.front() == buffer.back()) {
                this->lines.push_back(buffer);
                continue;
            }
            else if(areEqual<T>(buffer.front().x, buffer.back().x)) {
                if( areEqual<T>(buffer.front().x, bbox.xmin) || areEqual<T>(buffer.front().x, bbox.xmax) ) {
                        buffer.push_back(Vec<T>(buffer.front()));
                        this->lines.push_back(buffer);
                        continue;
                }
            }
            else if(areEqual<T>(buffer.front().y, buffer.back().y)) {
                if( areEqual<T>(buffer.front().y, bbox.ymin) || areEqual<T>(buffer.front().y, bbox.ymax) ) {
                        buffer.push_back(Vec<T>(buffer.front()));
                        this->lines.push_back(buffer);
                        continue;
                }
            }
            else {
                SearchBorder<double> sb(buffer.front(), bbox, isoline.value, data);
                    
                Line<T> segment;
                segment.push_back(buffer.back());

                //std::cout << sb;

                for (unsigned int i = 0; i < 4; i++) {
                    sb.match(&segment);
                    for (auto &line : mlines) {
                        sb.match(&line);
                    }
                    if(sb.matchedLines.empty()) {
                        sb++;
                        //std::cout << "continue search" << std::endl << sb;
                        buffer.push_front(sb.v);
                    }
                    else {
                        //std::cout << "break i=" << i << " !";
                        break;
                    }
                }

                if(sb.matchedLines.empty()) {
                    //std::cout << "Failed!!" << std::endl;
                    continue;
                }
                else {
                    //std::cout << "Success!!" << std::endl;
                    MatchedLine<T> bestMatch = sb.extractBestMatch();
                    assert(bestMatch.line != 0);

                    if(bestMatch.pos == FRONT)
                        bestMatch.line->reverse();
                    buffer.splice(buffer.begin(), *(bestMatch.line));

                    if(bestMatch.line->size() != 1)
                        mlines.remove(*bestMatch.line);

                    if(buffer.front() ==  buffer.back())
                            this->lines.push_back(buffer);
                    else
                            mlines.push_front(buffer);
                    
                    continue;
                }
            }
        }
    }

#endif /* end of include guard: ISOCONTOUR_H */
