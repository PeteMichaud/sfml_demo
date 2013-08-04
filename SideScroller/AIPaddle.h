//
//  AIPaddle.h
//  SideScroller
//
//  Created by Pete Michaud on 8/4/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#pragma once
#include "VisibleGameObject.h"

class AIPaddle :
    public VisibleGameObject
{
public:
    AIPaddle(void);
    ~AIPaddle(void);

    void Update(float elapasedTime);
    void Draw(sf::RenderWindow& rw);

    float GetVelocity() const;

private:
    float _velocity;
    float _maxVelocity;
};