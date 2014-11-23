
template <typename F, unsigned int N>
IsoLineGenerator<F,N>::IsoLineGenerator(unsigned int dataWidth, unsigned int dataHeight, BoundingBox<double> bbox) :
    dataWidth(dataWidth), dataHeight(dataHeight), bbox(bbox) {
}

template <typename F, unsigned int N>
ColorLineList<double,N> IsoLineGenerator<F,N>::generateIsoline(F* density, double isovalue, Color<N> color) 
{
    ColorLineList<double,4u> colorLines;
    LineList<double> computedLines;
    
    double width = bbox.xmax - bbox.xmin;
    double height = bbox.ymax - bbox.ymin;
    Vec<double> currentPos;
    
    double squareWidth = width/(dataWidth - 1);
    double squareHeight = height/(dataHeight - 1);
    Vec<double> squareSize(squareWidth, -squareHeight, 0.0); //minus sign because of coordinate change

    double d[4];
    double mean;
    
    unsigned char msCase, nLines;
    char lineTable[4];
    
    for (unsigned int y = 0; y < dataHeight-1; y++) {
        for (unsigned int x = 0; x < dataWidth-1; x++) {

            //DOUBLE MANDATORY (2h de debug pour de l'arithmetique des flottants...)
            d[0] =  static_cast<double>(density[(y+1)*dataWidth + x+0]);
            d[1] =  static_cast<double>(density[(y+1)*dataWidth + x+1]);
            d[2] =  static_cast<double>(density[(y+0)*dataWidth + x+1]);
            d[3] =  static_cast<double>(density[(y+0)*dataWidth + x+0]);

            msCase = computeCase(d,isovalue);
            nLines = MarchingSquare::lineCount[msCase];

            if(nLines == 0)
                continue;

            currentPos.x = bbox.xmin + x*squareWidth;
            currentPos.y = bbox.ymin + (y+1)*squareHeight;
            currentPos.z = 0.0;

            memcpy(lineTable, MarchingSquare::lineTable + 4*msCase, 4*sizeof(char));
            
#ifdef _DEBUG
            std::cout << d[3] << " " << d[2] << " " << d[1] << " " << d[0] << std::endl;
            std::cout << (d[3]>=isovalue) << " " << (d[2]>=isovalue) << " " << (d[1]>=isovalue) << " " << (d[0]>=isovalue) << std::endl;
            std::cout << static_cast<unsigned int>(msCase) << "  " << static_cast<unsigned int>(nLines) << std::endl;
#endif

            if(nLines == 2) {
                mean = (d[0] + d[1] + d[2] + d[3])/4.0;
                if((msCase == 0b1010 && mean >= isovalue) || (msCase == 0b0101 && mean < isovalue))
                    std::swap<char>(lineTable[0], lineTable[2]);
            }

            double alpha;

            for (unsigned int n = 0; n < nLines; n++) {
                Line<double> segment; 
                for (unsigned int e = 0; e < 2u; e++) {
                    unsigned char edge = static_cast<unsigned char>(lineTable[2*n+e]);
                    Vec<double> edgeStart(MarchingSquare::edgeStart[2*edge+0], MarchingSquare::edgeStart[2*edge+1], 0.0);
                    Vec<double> edgeDir(MarchingSquare::edgeDir[2*edge+0], MarchingSquare::edgeDir[2*edge+1], 0.0);
    
                    if(Utils::areEqual<double>(d[(edge+1)%4], d[edge]))
                        alpha = 0.5;
                    else 
                        alpha = (isovalue - d[edge])/(d[(edge+1)%4] - d[edge]);
                    
                    Vec<double> P = currentPos + (edgeStart + alpha*edgeDir)*squareSize;

                    segment.push_back(P);
#ifdef _DEBUG
                    std::cout << "Edge: " << static_cast<int>(edge) << std::endl;
                    std::cout << "EdgeStart: " << edgeStart << std::endl;
                    std::cout << "EdgeDir: " << edgeDir << std::endl;
                    std::cout << "Isovalue:" << isovalue << std::endl;
                    std::cout << "D0: " << d[edge] << std::endl;
                    std::cout << "D1: " << d[(edge+1)%4] << std::endl;
                    std::cout << "Alpha: " << alpha << " " << std::endl;
                    assert(alpha >= 0.0);
                    assert(alpha <= 1.0);
#endif
                }
                
                attachLine(segment, computedLines);
            }
        }
    }
   
    for (auto &line : computedLines) {
        colorLines.push_back(ColorLine<double,4u>(line, color));
    }
    
    return colorLines;
}

template <typename F, unsigned int N>
inline void IsoLineGenerator<F,N>::test() {

    LineList<double> ll;

    Line<double> segment0;
    Line<double> segment1;
    Line<double> segment2;
    Line<double> segment3;
    Line<double> segment4;
    Line<double> segment5;
   
    double eps = std::numeric_limits<double>::epsilon();
    Vec<double> P0(eps,0,0);
    Vec<double> P1(0,eps,0);
    Vec<double> P2(0,0,eps);
    Vec<double> P3(eps,eps,0);
    Vec<double> P4(eps,0,eps);
    Vec<double> P5(0,eps,eps);
    
    segment0.push_back(P0);
    segment0.push_back(P1);
    
    segment1.push_back(P1);
    segment1.push_back(P2);

    segment2.push_back(P2);
    segment2.push_back(P3);
    
    segment3.push_back(P3);
    segment3.push_back(P4);
    
    segment4.push_back(P4);
    segment4.push_back(P5);

    attachLine(segment4, ll);
    attachLine(segment0, ll);
    attachLine(segment2, ll);
    attachLine(segment1, ll);
    attachLine(segment3, ll);

    for (auto &line : ll) {
        for(auto &pt : line) {
            std::cout << pt << "=>";
        }
        std::cout << std::endl;
    }
}
        
template <typename F, unsigned int N>
inline unsigned char IsoLineGenerator<F,N>::computeCase(double d[], double isovalue) {
    return ((d[0] >= isovalue) << 0) +  ((d[1] >= isovalue) << 1) 
        +  ((d[2] >= isovalue) << 2) +  ((d[3] >= isovalue) << 3);
}
        
template <typename F, unsigned int N>
void IsoLineGenerator<F,N>::attachLine(Line<double> &line, LineList<double> &lineList) {

    LineList<double>::iterator it;

    for (it = lineList.begin(); it != lineList.end(); ++it) {
        if(it->front() == line.back()) {
            line.pop_back();
            line.splice(line.end(), *it,  it->begin(), it->end());
            break;
        }
        if(it->front() == line.front()) {
            line.pop_front();
            line.reverse();
            line.splice(line.end(), *it, it->begin(), it->end());
            break;
        }
        if(it->back() == line.front()) {
            line.pop_front();
            line.splice(line.begin(), *it, it->begin(), it->end());
            break;
        }
        if(it->back() == line.back()) {
            line.pop_back();
            line.reverse();
            line.splice(line.begin(), *it, it->begin(), it->end());
            break;
        }
    }   
    if(it->empty()) {
        lineList.remove(*it);
        attachLine(line, lineList);
    }
    else { 
        lineList.push_back(line);
    }
}
