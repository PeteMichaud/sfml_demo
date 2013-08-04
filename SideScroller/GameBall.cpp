//
//  GameBall.cpp
//  SideScroller
//
//  Created by Pete Michaud on 8/3/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#include "stdafx.h"

#include "GameBall.h"
#include "Game.h"

GameBall::GameBall() :
_velocity(230.0f),
_elapsedTimeSinceStart(0.0f)
{
    Load(resourcePath("ball.png"));
    assert(IsLoaded());

    GetSprite().setOrigin(15,15);

    std::srand(std::time(0));
    _angle = (float)(std::rand() / RAND_MAX * 360);
}

GameBall::~GameBall()
{
    
}

void GameBall::Update(float elapsedTime)
{
    _elapsedTimeSinceStart += elapsedTime;

    //if (_elapsedTimeSinceStart < 3.0f)
    //   return;

    float moveAmount = _velocity * elapsedTime;

    float moveByX = LinearVelocityX(_angle) * moveAmount;
    float moveByY = LinearVelocityY(_angle) * moveAmount;

    //collisde with the left side of the screen
    if(GetPosition().x + moveByX <= 0 + GetWidth()/2
       || GetPosition().x + GetHeight()/2 + moveByX >= Game::SCREEN_WIDTH)
    {
        //Ricochet
        _angle = 360.0f - _angle;
        if(_angle > 260.0f && _angle < 280.0f) _angle += 20.0f;
        if(_angle > 80.0f && _angle < 100.0f) _angle += 20.0f;
        moveByX = -moveByX;
    }

    PlayerPaddle* player1 =
        dynamic_cast<PlayerPaddle*>(Game::GameObjects().Get("Paddle1"));

    if (player1 != NULL)
    {
        sf::FloatRect p1BB = player1->GetBoundingRect();

        if (p1BB.intersects(GetBoundingRect()))
        {
            _angle = 360.0f - (_angle - 180.0f);
            if(_angle > 360.0f) _angle -= 360.0f;

            moveByY = -moveByY;

            // Make sure ball isn't inside paddle
            if (GetBoundingRect().width > player1->GetBoundingRect().top)
            {
                SetPosition(GetPosition().x, player1->GetBoundingRect().top - GetWidth()/2 - 1);
            }

            float playerVelocity = player1->GetVelocity();

            if(playerVelocity < 0)
            {
                _angle -= 20.0f;
                if (_angle < 0) _angle = 360.0f - _angle;
            }
            else if(playerVelocity > 0)
            {
                _angle += 20.0f;
                if (_angle > 360.0f) _angle = _angle - 360.0f;
            }

            _velocity += 5.0f;
        }

        if (GetPosition().y - GetHeight()/2 <= 0)
        {
            _angle = 180 - _angle;
            moveByY = -moveByY;
        }

        if (GetPosition().y + GetHeight()/2 + moveByY >= Game::SCREEN_HEIGHT)
        {
            GetSprite().setPosition(Game::SCREEN_WIDTH/2, Game::SCREEN_HEIGHT/2);
            _angle = (float)(std::rand() / RAND_MAX * 360);
            _velocity = 230.0f;
            _elapsedTimeSinceStart = 0.0f;
        }

        GetSprite().move(moveByX, moveByY);
    }
}

float GameBall::LinearVelocityX(float angle)
{
    angle -= 90;
    if (angle < 0) angle = 360 + angle;
    return (float)std::cos( angle * (3.1415926 / 180.0f));
}

float GameBall::LinearVelocityY(float angle)
{
    angle -= 90;
    if (angle < 0) angle = 360 + angle;
    return (float)std::sin( angle * (3.1415926 / 180.0f));
}