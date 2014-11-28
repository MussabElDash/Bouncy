//
//  Macros.h
//  Bouncy
//
//  Created by Omar Ahmed on 11/28/14.
//  Copyright (c) 2014 oa12gb. All rights reserved.
//

#ifndef Bouncy_Macros_h
#define Bouncy_Macros_h

#include <utility>
#include <vector>

#define POINT std::pair<int, std::pair<int, int> >
#define MAKE_POINT(x,y,z) std::make_pair(x, std::make_pair(y, z))
#define X first.first
#define Y second.first
#define Z second.second

#endif
