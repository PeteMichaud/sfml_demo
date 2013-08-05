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

    void Update(float elapasedTime);
    void Draw(sf::RenderWindow& rw);
    virtual void HandleInput() = 0;

    float GetVelocity() const;

protected:
    float _velocity;
    float _maxVelocity;
    void ClampVelocity();
    void WallCollision();

private:
    float ClampToScreen(float x);
};