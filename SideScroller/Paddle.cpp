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
#include "stringhelpers.h"

Paddle::Paddle() :
_velocity(0),
_maxVelocity(600.0f)
{
    GetRect().setSize(sf::Vector2f(300,30));
    GetRect().setFillColor(sf::Color::Black);
    CenterOrigin();
}

Paddle::~Paddle()
{

}

void Paddle::Draw(sf::RenderWindow& rw)
{
    VisibleGameObject::Draw(rw);
//    std::string strCoords =
//        "(" + zero_pad(GetPosition().x) + "," + zero_pad(GetPosition().y) + ")";
//    rw.draw(DebugText(
//        strCoords,
//        sf::Vector2f(50,GetPosition().y + GetHeight())));
//
//    std::string strSize =
//    "(" + to_s(GetWidth()) + "," + to_s(GetHeight()) + ")";
//    rw.draw(DebugText(
//        strSize,
//        sf::Vector2f(50,GetPosition().y + GetHeight()*1.5)));

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

    GetRect().move(_velocity * elapsedTime, 0);
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

    if(pos.x < GetRect().getGlobalBounds().width/2
       || pos.x > (Game::SCREEN_WIDTH - GetRect().getGlobalBounds().width/2))
    {
        SetPosition(ClampToScreen(pos.x), pos.y);
        _velocity = -_velocity;
    }
}

float Paddle::ClampToScreen(float x)
{
    return clamp(x,
        GetRect().getGlobalBounds().width/2,
        (Game::SCREEN_WIDTH - GetRect().getGlobalBounds().width/2));
}

void Paddle::SetColor(sf::Color color)
{
    GetRect().setFillColor(color);
}

void Paddle::Whittle(float amount)
{
    sf::Vector2f currentSize = GetRect().getSize();
    GetRect().setSize(sf::Vector2f(
        currentSize.x - amount,
        currentSize.y
        ));
    CenterOrigin();
}

void Paddle::CenterOrigin()
{

    GetRect().setOrigin(
        GetRect().getGlobalBounds().width / 2,
        GetRect().getGlobalBounds().height / 2);
}