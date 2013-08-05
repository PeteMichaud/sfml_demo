//
//  PlayerPaddle.h
//  SideScroller
//
//  Created by Pete Michaud on 8/3/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#pragma once
#include "Paddle.h"

class PlayerPaddle :
    public Paddle
{
public:
    void Update(float elapsedTime);
};