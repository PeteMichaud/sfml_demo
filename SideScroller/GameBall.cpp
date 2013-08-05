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

    Set();
}

GameBall::~GameBall()
{
    
}

void GameBall::Update(float elapsedTime)
{
    _elapsedTimeSinceStart += elapsedTime;

    if (_elapsedTimeSinceStart < 3.0f)
       return;

    sf::Vector2f moveBy = GetMovementVector(elapsedTime);

    moveBy = CheckWallCollisions(moveBy);

    PlayerPaddle* player1 =
        dynamic_cast<PlayerPaddle*>(Game::GameObjects().Get("Paddle1"));
    AIPaddle* player2 =
    dynamic_cast<AIPaddle*>(Game::GameObjects().Get("Paddle2"));

    moveBy = CheckPaddleCollision(moveBy, (Paddle*)player1);
    moveBy = CheckPaddleCollision(moveBy, (Paddle*)player2);

    GetSprite().move(moveBy);
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

void GameBall::Set()
{
    _elapsedTimeSinceStart = 0.0f;
    
    GetSprite().setOrigin(
        GetSprite().getGlobalBounds().width/2,
        GetSprite().getGlobalBounds().height/2);

    GetSprite().setPosition(Game::SCREEN_WIDTH/2, Game::SCREEN_HEIGHT/2);

    std::srand(std::time(0));
    _angle = std::rand() % 360 + 1;
    _velocity = 230.0f;
}

void GameBall::Reset()
{
    Set();
}

sf::Vector2f GameBall::CheckWallCollisions(sf::Vector2f moveBy)
{
    //collide with the side of the screen
    if(GetPosition().x + moveBy.x <= 0 + GetWidth()/2
       || GetPosition().x + GetHeight()/2 + moveBy.x >= Game::SCREEN_WIDTH)
    {
        //Ricochet
        _angle = 360.0f - _angle;
        if(_angle > 260.0f && _angle < 280.0f) _angle += 20.0f;
        if(_angle > 80.0f && _angle < 100.0f) _angle += 20.0f;
        moveBy.x = -moveBy.x;
        ServiceLocator::GetAudio()->PlaySound("ping.wav");
    }

    if (GetPosition().y + moveBy.y <= 0 + GetHeight()/2)
    {
        _angle = 180.0f - _angle;
        moveBy.y = -moveBy.y;
        ServiceLocator::GetAudio()->PlaySound("ping.wav");
    }

    if (GetPosition().y + GetHeight()/2 + moveBy.y >= Game::SCREEN_HEIGHT)
    {
        Paddle* player1 =
        dynamic_cast<Paddle*>(Game::GameObjects().Get("Paddle1"));
        player1->Whittle(-5.0f);
        Reset();
    }

    return moveBy;
}

sf::Vector2f GameBall::CheckPaddleCollision(sf::Vector2f moveBy, Paddle* paddle)
{
    if (paddle != NULL)
    {
        if (paddle->GetBoundingRect().intersects(GetBoundingRect()))
        {
            ServiceLocator::GetAudio()->PlaySound("ping.wav");
            paddle->SetColor(RandomColor());
            paddle->Whittle();
            _angle = 360.0f - (_angle - 180.0f);
            if(_angle > 360.0f) _angle -= 360.0f;

            moveBy.y = -moveBy.y;

            float newY;
            if (GetPosition().y < Game::SCREEN_HEIGHT/2)
            {
                newY = paddle->GetBoundingRect().top
                        + paddle->GetHeight()
                        + (GetHeight()/2)
                        + 1;
            }
            else
            {
                newY = paddle->GetBoundingRect().top
                        //- (paddle->GetHeight()/2)
                        - (GetHeight()/2)
                        - 1;
            }
            SetPosition(GetPosition().x,newY);

            float objectVelocity = paddle->GetVelocity();

            if(objectVelocity < 0)
            {
                _angle -= 20.0f;
                if (_angle < 0) _angle = 360.0f - _angle;
            }
            else if(objectVelocity > 0)
            {
                _angle += 20.0f;
                if (_angle > 360.0f) _angle = _angle - 360.0f;
            }
            
            _velocity += 5.0f;
        }
    }
    
    return moveBy;
}

sf::Vector2f GameBall::GetMovementVector(float elapsedTime)
{
    float moveAmount = _velocity * elapsedTime;

    return *new sf::Vector2f(
        LinearVelocityX(_angle) * moveAmount,
        LinearVelocityY(_angle) * moveAmount);
}

sf::Color GameBall::RandomColor()
{
    std::srand(std::time(0));
    int r = std::rand() % 255;
    int g = std::rand() % 255;
    int b = std::rand() % 255;

    return sf::Color(r,g,b);
}