//
//  Paddle.cpp
//  SideScroller
//
//  Created by Pete Michaud on 8/3/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#include "stdafx.h"
#include "Paddle.h"
#include "Game.h"

Paddle::Paddle() :
_velocity(0),
_maxVelocity(600.0f)
{
    Load(resourcePath("paddle.png"));
    assert(IsLoaded());

    GetSprite().setOrigin(GetSprite().getGlobalBounds().width / 2, GetSprite().getGlobalBounds().height / 2);
}

Paddle::~Paddle()
{

}

void Paddle::Draw(sf::RenderWindow& rw)
{
    VisibleGameObject::Draw(rw);
}

float Paddle::GetVelocity() const
{
    return _velocity;
}