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
#include "PlayerPaddle.h"
#include "AIPaddle.h"

#include "Emitter.h"
#include "Spark.h"
#include "PlayScreen.h"

#include "stringhelpers.h"
#include "mathhelpers.h"

GameBall::GameBall() :
_velocity(330.0f),
_elapsedTimeSinceStart(0.0f)
{
    _centerScreen = sf::Vector2f(Game::SCREEN_WIDTH/2, Game::SCREEN_HEIGHT/2);

    Load(resourcePath("sphere4.png"));
    assert(IsLoaded());

    _sphereShader.loadFromFile(
         resourcePath("sphere.vert"),
         resourcePath("sphere.frag"));
    _sphereShader.setParameter("tex0", sf::Shader::CurrentTexture);

    Set();

    LoadShadows();
}

GameBall::~GameBall()
{
    
}

void GameBall::LoadShadows()
{
    _shadowSmallTexture.loadFromFile(resourcePath("ball_shadow_small.png"));
    _shadowSmall.setTexture(_shadowSmallTexture);
    _shadowBigTexture.loadFromFile(resourcePath("ball_shadow_big.png"));
    _shadowBig.setTexture(_shadowBigTexture);

    _shadowSmall.setOrigin(30,30);
    _shadowBig.setOrigin(30,30);

    _shadowSmall.setPosition(ShadowOffset(1.015));
    _shadowBig.setPosition(ShadowOffset(1.03));
}

void GameBall::Update(float elapsedTime)
{
    _elapsedTimeSinceStart += elapsedTime;

    if (_elapsedTimeSinceStart < 3.0f)
       return;

    sf::Vector2f moveBy = GetMovementVector(elapsedTime);

    moveBy = CheckWallCollisions(moveBy);

    PlayerPaddle* player1 =
        dynamic_cast<PlayerPaddle*>(PlayScreen::GameObjects()->Get("Paddle1"));
    AIPaddle* player2 =
    dynamic_cast<AIPaddle*>(PlayScreen::GameObjects()->Get("Paddle2"));

    moveBy = CheckPaddleCollision(moveBy, (Paddle*)player1);
    moveBy = CheckPaddleCollision(moveBy, (Paddle*)player2);

    _sphereShader.setParameter("pos", GetPosition());
    
    GetSprite().move(moveBy);
    _shadowSmall.setPosition(ShadowOffset(1.015));
    _shadowBig.setPosition(ShadowOffset(1.03));
}

void GameBall::Draw(sf::RenderWindow& renderWindow)
{
    renderWindow.draw(_shadowBig);
    renderWindow.draw(_shadowSmall);
    renderWindow.draw(GetSprite(), &_sphereShader);
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

    GetSprite().setPosition(_centerScreen);

    std::srand(std::time(0));
    _angle = randf(360);
    _velocity = 330.0f;
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
        Crash();
        PlayScreen::GetCamera().Shake(15.0f, 0.5f);
        Spark(moveBy);
    }

    //top
    if (GetPosition().y + moveBy.y <= 0 + GetHeight()/2)
    {
        _angle = 180.0f - _angle;
        moveBy.y = -moveBy.y;
        Crash();
    }

    //bottom
    if (GetPosition().y + GetHeight()/2 + moveBy.y >= Game::SCREEN_HEIGHT)
    {
        Paddle* player1 =
        dynamic_cast<Paddle*>(PlayScreen::GameObjects()->Get("Paddle1"));
        player1->Whittle(-5.0f);
        Reset();
    }

    return moveBy;
}

void GameBall::Spark(sf::Vector2f direction) const
{
    Particles::Spark* ps =
        new Particles::Spark(-direction);
    Particles::Emitter* sparks = new Particles::Emitter(
        ps,
        GetPosition(),
        100,
        0.001f,
        100);

    PlayScreen::GameObjects()->Add("Sparks" + to_s(sparks), sparks);
    
}

void GameBall::Crash() const
{
    ServiceLocator::GetAudio()->PlaySound("crash" + to_s(std::rand()%_crashes) + ".ogg");
}

sf::Vector2f GameBall::CheckPaddleCollision(sf::Vector2f moveBy, Paddle* paddle)
{
    if (paddle != NULL)
    {
        if (paddle->GetBoundingRect().intersects(GetBoundingRect()))
        {
            ServiceLocator::GetAudio()->PlaySound("paddle_explosion.wav");
            //paddle->SetColor(RandomColor());
            paddle->Whittle();
            PlayScreen::GetCamera().Shake(25.0f, 1.0f);
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

sf::Vector2f GameBall::ShadowOffset(float magnitude)
{
    sf::Vector2f relative =
        (GetSprite().getPosition() - _centerScreen) * magnitude;

    return relative + _centerScreen;
}
