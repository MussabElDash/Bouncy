//
//  Wall.cpp
//  Bouncy
//
//  Created by Omar Ahmed on 11/28/14.
//  Copyright (c) 2014 oa12gb. All rights reserved.
//

#include "Wall.h"

Wall::Wall(POINT startCorner,
           POINT endCorner,
           POINT deltaVector,
           void (*pushMatrix)(),
           void (*popMatrix)(),
           void (*translate)(double, double, double),
           void (*scale)(double, double, double),
           void (*cube)(double),
           void (*clearColor)(double, double, double)){
    this->startCorner = startCorner;
    this->endCorner = endCorner;
    this->deltaVector = deltaVector;
    
    this->pushMatrix = pushMatrix;
    this->popMatrix = popMatrix;
    this->translate = translate;
    this->scale = scale;
    this->cube = cube;
    this->clearColor = clearColor;
    
    printf("%lf %lf %lf\n", deltaVector.X, startCorner.X, endCorner.X);
    int xSize = (endCorner.X - startCorner.X) / deltaVector.X;
    int ySize = (endCorner.Y - startCorner.Y) / deltaVector.Y;
    int zSize = (endCorner.Z - startCorner.Z) / deltaVector.Z;
    
    this->size = MAKE_COLOR(xSize, ySize, zSize);
    for(int x = 0; x < xSize; x++){
        std::vector<std::vector<COLOR>> additx;
        for(int y = 0; y < ySize; y++){
            std::vector<COLOR> addity;
            for(int z = 0; z < zSize; z++){
                addity.push_back(MAKE_COLOR((rand() % 256) / 255.0, (rand() % 256) / 255.0, (rand() % 256) / 255.0));
            }
            additx.push_back(addity);
        }
        this->wallColors.push_back(additx);
    }
}

void Wall::draw(){
    for(int x = 0; x < size.X; x++){
        for(int y = 0; y < size.Y; y++){
            for(int z = 0; z < size.Z; z++){
                drawCube(MAKE_POINT(x, y, z));
            }
        }
    }
}

void Wall::drawCube(COLOR cubeCell){
    COLOR cubeColor = wallColors[cubeCell.X][cubeCell.Y][cubeCell.Z];
    pushMatrix();
    clearColor(cubeColor.R, cubeColor.G, cubeColor.B);
    translate(cubeCell.X * deltaVector.X + startCorner.X,
              cubeCell.Y * deltaVector.Y + startCorner.Y,
              cubeCell.Z * deltaVector.Z + startCorner.Z);
    scale(deltaVector.X, deltaVector.Y, deltaVector.Z);
    cube(1);
    popMatrix();
}

// If the ball hits this wall, returns the score of this hit, else return 0
int Wall::getScore(POINT center, int radius){
    return 0;
}

int Wall::getCellScore(POINT point){
    COLOR color = wallColors[point.X][point.Y][point.Z];
    return (color.R - color.G) * color.B;
}