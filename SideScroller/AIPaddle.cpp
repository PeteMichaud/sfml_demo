//
//  AIPaddle.cpp
//  SideScroller
//
//  Created by Pete Michaud on 8/3/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#include "stdafx.h"
#include "AIPaddle.h"
#include "Game.h"
#include "GameBall.h"

void AIPaddle::Update(float elapsedTime)
{
    const GameBall* gameBall = static_cast<GameBall*>
    (Game::GameObjects().Get("Ball"));

    sf::Vector2f ballPosition = gameBall->GetPosition();

    if(GetPosition().x - 20 < ballPosition.x)
        _velocity += 15.0f;
    else if(GetPosition().x + 20 > ballPosition.x)
        _velocity -= 15.0f;
    else
        _velocity = 0.0f;
    
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