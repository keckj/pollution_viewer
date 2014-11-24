
#ifndef ISOLINEUTILS_H
#define ISOLINEUTILS_H

namespace MarchingSquare {
    static unsigned char lineCount[16] = {
        0,1,1,1,
        1,2,1,1,
        1,1,2,1,
        1,1,1,0
    };

    //max 2*2 vertices
    static char lineTable[64] = {
        -1,-1,-1,-1, // 0
        0,3,-1,-1,   // 1
        0,1,-1,-1,   // 1
        1,3,-1,-1,   // 1

        1,2,-1,-1,   // 1
        1,2,3,0,     // 2
        0,2,-1,-1,   // 1
        2,3,-1,-1,   // 1

        2,3,-1,-1,   // 1
        0,2,-1,-1,   // 1
        1,2,3,0,     // 2
        1,2,-1,-1,   // 1

        1,3,-1,-1,   // 1
        0,1,-1,-1,   // 1
        0,3,-1,-1,   // 1
        0,0,-1,-1,   // 0
    };

    //(X,Y)
    static double edgeStart[8] = {
        0.0, 0.0, 
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0
    };

    //(X,Y)
    static double edgeEnd[8] = { 
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0,
        0.0, 0.0 
    };

    //(VX,VY)
    static double edgeDir[8] = { 
        1.0, 0.0,
        0.0, 1.0,
        -1.0, 0.0,
        0.0, -1.0
    };
}

#endif /* end of include guard: ISOLINEUTILS_H */
