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
    Wall(POINT startCorner, POINT endCorner, POINT deltaVector);
    void draw();
    int getScore(POINT center, int radius);
private:
    std::vector<std::vector<POINT> > wallColors;
};

#endif /* defined(__Bouncy__Wall__) */
