//
//  Wall.cpp
//  Bouncy
//
//  Created by Omar Ahmed on 11/28/14.
//  Copyright (c) 2014 oa12gb. All rights reserved.
//

#include "Wall.h"

Wall::Wall(POINT startCorner, POINT endCorner, POINT deltaVector){
    int xSize = (endCorner.X - startCorner.X + deltaVector.X - 1) / deltaVector.X;
    int ySize = (endCorner.Y - startCorner.Y + deltaVector.Y - 1) / deltaVector.Y;
    int zSize = (endCorner.Z - startCorner.X + deltaVector.X - 1) / deltaVector.Z;
    
    wallColors = std::vector<std::vector<std::vector<COLOR>>>(
        xSize,
        std::vector<std::vector<COLOR>>(
            ySize,
            std::vector<COLOR>(
                zSize,
                MAKE_COLOR(rand() % 256, rand() % 256, rand() % 256)
            )
        )
    );
}

// Draw a wall and keep it in the stack
void Wall::draw(){
    
}

// If the ball hits this wall, returns the score of this hit, else return 0
int Wall::getScore(POINT center, int radius){
    return 0;
}

int Wall::getCellScore(POINT point){
    COLOR color = wallColors[point.X][point.Y][point.Z];
    return (color.R - color.G) * color.B;
}