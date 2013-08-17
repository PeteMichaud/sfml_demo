//
//  SplashScreen.h
//  SideScroller
//
//  Created by Pete Michaud on 8/3/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#pragma once
#include "stdafx.h"
#include "GameState.h"

class SplashScreen :
    public GameState
{
public:
    SplashScreen(sf::RenderWindow* rw);
    void Initialize();
    void Loop();

private:
    sf::Texture _texture;
    sf::Sprite _sprite;
};