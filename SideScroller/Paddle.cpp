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
#include "mathhelpers.h"

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

void Paddle::Update(float elapsedTime)
{
    HandleInput();

    ClampVelocity();

    WallCollision();

    GetSprite().move(_velocity * elapsedTime, 0);
}

void Paddle::ClampVelocity()
{
    if (_velocity > _maxVelocity)
        _velocity = _maxVelocity;

    if (_velocity < -_maxVelocity)
        _velocity = -_maxVelocity;
}

void Paddle::WallCollision()
{
    sf::Vector2f pos = this->GetPosition();

    if(pos.x < GetSprite().getGlobalBounds().width/2
       || pos.x > (Game::SCREEN_WIDTH - GetSprite().getGlobalBounds().width/2))
    {
        SetPosition(ClampToScreen(pos.x), pos.y);
        _velocity = -_velocity;
    }
}

float Paddle::ClampToScreen(float x)
{
    return clamp(x,
        GetSprite().getGlobalBounds().width/2,
        (Game::SCREEN_WIDTH - GetSprite().getGlobalBounds().width/2));
}