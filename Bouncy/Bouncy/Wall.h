//
//  Wall.h
//  Bouncy
//
//  Created by Omar Ahmed on 11/28/14.
//  Copyright (c) 2014 oa12gb. All rights reserved.
//

#ifndef __Bouncy__Wall__
#define __Bouncy__Wall__

#include "Macros.h"

class Wall{
public:
    Wall(POINT startCorner,
         POINT endCorner,
         POINT deltaVector,
         void (*pushMatrix)(),
         void (*popMatrix)(),
         void (*translate)(double, double, double),
         void (*scale)(double, double, double),
         void (*cube)(double),
         void (*clearColor)(double, double, double));
    
    void draw();
    int getScore(POINT center, int radius);
private:
    POINT size;
    POINT startCorner;
    POINT endCorner;
    POINT deltaVector;
    std::vector<std::vector<std::vector<COLOR>>> wallColors;
    
    int getCellScore(POINT point);
    void drawCube(COLOR cube);
    void drawQuad(POINT C1, POINT C2, COLOR quadColor);
    
    //OpenGL functions
    void (*pushMatrix)();
    void (*translate)(double, double, double);
    void (*scale)(double, double, double);
    void (*cube)(double);
    void (*popMatrix)();
    void (*clearColor)(double, double, double);
    
};

#endif /* defined(__Bouncy__Wall__) */
