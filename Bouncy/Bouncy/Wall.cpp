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
           POINT planeVector,
           void (*pushMatrix)(),
           void (*popMatrix)(),
           void (*translate)(double, double, double),
           void (*scale)(double, double, double),
           void (*cube)(double),
           void (*clearColor)(double, double, double)){
    this->startCorner = startCorner;
    this->endCorner = endCorner;
    this->deltaVector = deltaVector;
    this->planeVector = planeVector;
    
    this->pushMatrix = pushMatrix;
    this->popMatrix = popMatrix;
    this->translate = translate;
    this->scale = scale;
    this->cube = cube;
    this->clearColor = clearColor;
    
    printf("%lf %lf %lf\n", deltaVector.X, startCorner.X, endCorner.X);
    int xSize = fabs(endCorner.X - startCorner.X) / deltaVector.X;
    int ySize = fabs(endCorner.Y - startCorner.Y) / deltaVector.Y;
    int zSize = fabs(endCorner.Z - startCorner.Z) / deltaVector.Z;
    
    epsilon = deltaVector.X * planeVector.X + deltaVector.Y * planeVector.Y + deltaVector.Z * planeVector.Z;

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
int Wall::getScore(POINT center, double radius){
    double distX = fmin(fabs(center.X - startCorner.X), fabs(center.X - endCorner.X));
    double distY = fmin(fabs(center.Y - startCorner.Y), fabs(center.Y - endCorner.Y));
    double distZ = fmin(fabs(center.Z - startCorner.Z), fabs(center.Z - endCorner.Z));
    distX *= planeVector.X;
    distY *= planeVector.Y;
    distZ *= planeVector.Z;
    //printf("%lf %lf %lf, %lf %lf %lf\n", center.X, center.Y, center.Z, distX, distY, distZ);
    if(distX + distY + distZ <= epsilon + radius * 9.0 / 10 - 1e-9){
        return -111111111;
    }
    if(distX + distY + distZ <= radius + 1e-9 + epsilon && distX + distY + distZ >= epsilon + radius * 9.0 / 10 - 1e-9){
        center.X = fabs((center.X - startCorner.X) / deltaVector.X);
        center.Y = fabs((center.Y - startCorner.Y) / deltaVector.Y);
        center.Z = fabs((center.Z - startCorner.Z) / deltaVector.Z);

        center.X *= 1 - planeVector.X;
        center.Y *= 1 - planeVector.Y;
        center.Z *= 1 - planeVector.Z;

        //printf("..... %lf %lf %lf %lf %lf %lf\n", center.X, center.Y, center.Z, planeVector.X, planeVector.Y, planeVector.Z);
        //printf("%lf %lf %lf\n", size.X, size.Y, size.Z);
        return getCellScore(center);
    }
    return 0;
}

int Wall::getCellScore(POINT point){
    //printf("done1\n");
    COLOR color = wallColors[(int)(point.X)][(int)(point.Y)][(int)(point.Z)];
    //printf("done2 %lf\n", (color.R - color.G) * color.B * 100.0);
    int score = (color.G - color.B) * color.R * 100.0;
    return score == 0 ? 1 : score;
}