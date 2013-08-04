//
//  PlayerPaddle.h
//  SideScroller
//
//  Created by Pete Michaud on 8/3/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#pragma once
#include "VisibleGameObject.h"

class PlayerPaddle :
    public VisibleGameObject
{
public:
    PlayerPaddle();
    ~PlayerPaddle();

    void Update(float elapsedTime);
    void Draw(sf::RenderWindow& rw);

    float GetVelocity() const;

private:
    float _velocity;
    float _maxVelocity;
};