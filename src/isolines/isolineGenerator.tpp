
template <typename F, unsigned int N>
IsoLineGenerator<F,N>::IsoLineGenerator(unsigned int dataWidth, unsigned int dataHeight, BoundingBox<double> bbox) :
    dataWidth(dataWidth), dataHeight(dataHeight), bbox(bbox) {
}

template <typename F, unsigned int N>
ColorLineList<double,N> IsoLineGenerator<F,N>::generateIsoline(F* density, F isovalue, Color<N> color) 
{
    PointList<double> points;
    
    double width = bbox.xmax - bbox.xmin;
    double height = bbox.ymax - bbox.ymin;
    Vec<double> currentPos;
    
    double squareWidth = width/(dataWidth - 1);
    double squareHeight = height/(dataHeight - 1);
    Vec<double> squareSize(squareWidth, squareHeight, 0.0);

    F d[4];
    F mean;
    
    unsigned char msCase, nLines;
    char lineTable[4];
    
    for (unsigned int y = 0; y < dataHeight-1; y++) {
        for (unsigned int x = 0; x < dataWidth-1; x++) {

            d[0] =  density[(y+1)*dataWidth + x+0];
            d[1] =  density[(y+1)*dataWidth + x+1];
            d[2] =  density[(y+0)*dataWidth + x+1];
            d[3] =  density[(y+0)*dataWidth + x+0];

            msCase = computeCase(d,isovalue);
            nLines = MarchingSquare::lineCount[msCase];

            if(nLines == 0)
                continue;

            currentPos.x = bbox.xmin + x*squareWidth;
            currentPos.y = bbox.ymin + (y+1)*squareHeight;
            currentPos.z = 0.0;

            memcpy(lineTable, MarchingSquare::lineTable + 4*msCase, 4*sizeof(char));
                    
            //std::cout << d[3] << " " << d[2] << " " << d[1] << " " << d[0] << std::endl;
            //std::cout << (d[3]>=isovalue) << " " << (d[2]>=isovalue) << " " << (d[1]>=isovalue) << " " << (d[0]>=isovalue) << std::endl;
            //std::cout << static_cast<unsigned int>(msCase) << "  " << static_cast<unsigned int>(nLines) << std::endl;

            if(nLines == 2) {
                mean = (d[0] + d[1] + d[2] + d[3])/F(4);
                if((msCase == 0b1010 && mean >= isovalue) || (msCase == 0b0101 && mean < isovalue))
                    std::swap<char>(lineTable[0], lineTable[2]);
            }

            for (unsigned int n = 0; n < nLines; n++) {
                for (unsigned int e = 0; e < 2u; e++) {
                    unsigned char edge = static_cast<unsigned char>(lineTable[2*n+e]);
                    Vec<double> edgeStart(MarchingSquare::edgeStart[2*edge+0], MarchingSquare::edgeStart[2*edge+1], 0.0);
                    Vec<double> edgeDir(MarchingSquare::edgeDir[2*edge+0], MarchingSquare::edgeDir[2*edge+1], 0.0);

                    double alpha = (isovalue - d[edge])/(d[(edge+1)%4] - d[edge]);
                    
                    //std::cout << "Edge: " << static_cast<int>(edge) << std::endl;
                    //std::cout << "EdgeStart: " << edgeStart << std::endl;
                    //std::cout << "EdgeDir: " << edgeDir << std::endl;
                    //std::cout << "Isovalue:" << isovalue << std::endl;
                    //std::cout << "D0: " << d[edge] << std::endl;
                    //std::cout << "D1: " << d[(edge+1)%4] << std::endl;
                    //std::cout << "Alpha: " << alpha << " " << std::endl;
                    assert(alpha >= 0.0);
                    assert(alpha <= 1.0);
                    Vec<double> P = currentPos + (edgeStart + alpha*edgeDir)*squareSize;

                    points.push_back(P);
                }
            }
        }
    }

    ColorLineList<double,N> colorLines;


    while(!points.empty()) {
        ColorLine<double,N>(color);
        for(auto& p : points) {
            assert(p.x <= bbox.xmax);
            assert(p.x >= bbox.xmin);
            assert(p.y <= bbox.ymax);
            assert(p.y >= bbox.ymin);




        }
    }


    return colorLines;
}
        
template <typename F, unsigned int N>
inline unsigned char IsoLineGenerator<F,N>::computeCase(F d[], F isovalue) {
    return ((d[0] >= isovalue) << 0) +  ((d[1] >= isovalue) << 1) 
        +  ((d[2] >= isovalue) << 2) +  ((d[3] >= isovalue) << 3);
}
