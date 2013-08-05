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

void PlayerPaddle::HandleInput()
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
 }