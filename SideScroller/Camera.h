//
//  Camera.h
//  SideScroller
//
//  Created by Pete Michaud on 8/6/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#pragma once
#include "stdafx.h"

class Camera
{
public:
    Camera();
    ~Camera();
    void Update();
    void Shake(float magnitude, float duration);
    sf::View& GetView();
private:
    sf::View _view;
    sf::Clock _clock;
    float _shakeMagnitude;
    float _shakeDuration;
    float _shakeDurationStart;
};