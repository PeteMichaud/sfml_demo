//
//  GameState.h
//  SideScroller
//
//  Created by Pete Michaud on 8/17/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#pragma once
#include "stdafx.h"

class GameState
{
public:
    GameState(sf::RenderWindow* rw);
    ~GameState();

    virtual void Loop() = 0;
    virtual void Initialize() = 0;
    
protected:
    sf::RenderWindow* _rw;
};