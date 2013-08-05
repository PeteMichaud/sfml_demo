//
//  Paddle.h
//  SideScroller
//
//  Created by Pete Michaud on 8/4/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#pragma once
#include "VisibleGameObject.h"

class Paddle :
public VisibleGameObject
{
public:
    Paddle(void);
    ~Paddle(void);

    virtual void Update(float elapasedTime) = 0;
    void Draw(sf::RenderWindow& rw);

    float GetVelocity() const;

protected:
    float _velocity;
    float _maxVelocity;
};