//
//  AIPaddle.h
//  SideScroller
//
//  Created by Pete Michaud on 8/4/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#pragma once
#include "Paddle.h"

class AIPaddle :
    public Paddle
{
public:
    void HandleInput();
};