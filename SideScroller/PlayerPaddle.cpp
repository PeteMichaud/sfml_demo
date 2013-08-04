//
//  PlayerPaddle.cpp
//  SideScroller
//
//  Created by Pete Michaud on 8/3/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#include "stdafx.h"
#include "PlayerPaddle.h"
#include "Game.h"

PlayerPaddle::PlayerPaddle() :
_velocity(0),
_maxVelocity(600.0f)
{
    Load(resourcePath("paddle.png"));
    assert(IsLoaded());

    GetSprite().setOrigin(GetSprite().getGlobalBounds().width / 2, GetSprite().getGlobalBounds().height / 2);
}

PlayerPaddle::~PlayerPaddle()
{
    
}

void PlayerPaddle::Draw(sf::RenderWindow& rw)
{
    VisibleGameObject::Draw(rw);
}

float PlayerPaddle::GetVelocity() const
{
    return _velocity;
}

void PlayerPaddle::Update(float elapsedTime)
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        _velocity -= 3.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        _velocity += 3.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        _velocity = 0.0f;
    }

    if (_velocity > _maxVelocity)
        _velocity = _maxVelocity;

    if (_velocity < -_maxVelocity)
        _velocity = -_maxVelocity;

    sf::Vector2f pos = this->GetPosition();

    if(pos.x < GetSprite().getGlobalBounds().width/2
       || pos.x > (Game::SCREEN_WIDTH - GetSprite().getGlobalBounds().width/2))
    {
        _velocity = -_velocity;
    }

       GetSprite().move(_velocity * elapsedTime, 0);
}