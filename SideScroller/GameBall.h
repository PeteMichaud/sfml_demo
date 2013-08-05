//
//  GameBall.h
//  SideScroller
//
//  Created by Pete Michaud on 8/3/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#pragma once
#include "Paddle.h"

class GameBall :
    public VisibleGameObject
{
public:
    GameBall();
    virtual ~GameBall();
    void Update(float);

private:
    void Set();
    void Reset();
    sf::Vector2f CheckWallCollisions(sf::Vector2f moveBy);
    sf::Vector2f CheckPaddleCollision(sf::Vector2f moveBy, Paddle* object);
    sf::Vector2f GetMovementVector(float elapsedTime);
    float _velocity;
    float _angle;
    float _elapsedTimeSinceStart;

    float LinearVelocityX(float angle);
    float LinearVelocityY(float angle);
};