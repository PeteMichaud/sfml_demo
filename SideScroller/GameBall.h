//
//  GameBall.h
//  SideScroller
//
//  Created by Pete Michaud on 8/3/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#pragma once
#include "VisibleGameObject.h"

class GameBall :
    public VisibleGameObject
{
public:
    GameBall();
    virtual ~GameBall();
    void Update(float);

private:
    float _velocity;
    float _angle;
    float _elapsedTimeSinceStart;

    float LinearVelocityX(float angle);
    float LinearVelocityY(float angle);
};