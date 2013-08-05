//
//  mathhelpers.h
//  SideScroller
//
//  Created by Pete Michaud on 8/4/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

float clamp(float x, float a, float b)
{
    return x < a ? a : (x > b ? b : x);
}