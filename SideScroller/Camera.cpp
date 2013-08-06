//
//  Camera.cpp
//  SideScroller
//
//  Created by Pete Michaud on 8/6/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#include "Camera.h"
#include "Game.h"
#include "mathhelpers.h"

Camera::Camera()
{
    _view.reset(sf::FloatRect(0,0,Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT));
    _view.setViewport(sf::FloatRect(0.0,0.0,1.0,1.0));
    srand((unsigned)time(0));
}

Camera::~Camera()
{

}

sf::View& Camera::GetView()
{
    return _view;
}

void Camera::Update()
{
    float timeDelta = _clock.restart().asSeconds();
    _view.setCenter(Game::SCREEN_WIDTH/2, Game::SCREEN_HEIGHT/2);
    if (_shakeDuration > 0)
    {
        float magnitude =
            _shakeDuration / _shakeDurationStart * _shakeMagnitude;
        sf::Vector2f shakeBy(
            randf(magnitude, -magnitude),
            randf(magnitude, -magnitude));

        _view.move(shakeBy);
        _shakeDuration -= timeDelta;
    }
    
}

void Camera::Shake(float magnitude, float duration)
{
    _shakeMagnitude = magnitude;
    _shakeDuration = duration;
    _shakeDurationStart = duration;
}