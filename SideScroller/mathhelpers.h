//
//  mathhelpers.h
//  SideScroller
//
//  Created by Pete Michaud on 8/4/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

inline float clamp(float x, float a, float b)
{
    return x < a ? a : (x > b ? b : x);
}

inline float randf(float max, float min = 0.0)
{
    return min + (float)std::rand() / ((float)RAND_MAX / (max - min));
}