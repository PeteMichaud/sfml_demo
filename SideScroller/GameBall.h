//
//  GameBall.h
//  SideScroller
//
//  Created by Pete Michaud on 8/3/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#pragma once
#include "Paddle.h"

class GameBall :
    public VisibleGameObject
{
public:
    GameBall();
    virtual ~GameBall();
    void Update(float);
    void Draw(sf::RenderWindow&);
private:
    void Set();
    void Reset();
    sf::Vector2f CheckWallCollisions(sf::Vector2f moveBy);
    sf::Vector2f CheckPaddleCollision(sf::Vector2f moveBy, Paddle* object);
    sf::Vector2f GetMovementVector(float elapsedTime);
    float _velocity;
    float _angle;
    float _elapsedTimeSinceStart;

    float LinearVelocityX(float angle);
    float LinearVelocityY(float angle);

    sf::Color RandomColor();

    sf::Shader _sphereShader;

    void LoadShadows();
    sf::Sprite _shadowSmall;
    sf::Sprite _shadowBig;
    sf::Texture _shadowSmallTexture;
    sf::Texture _shadowBigTexture;

    sf::Vector2f ShadowOffset(float magnitude);

    sf::Vector2f _centerScreen;
};