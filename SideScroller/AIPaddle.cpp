//
//  AIPaddle.cpp
//  SideScroller
//
//  Created by Pete Michaud on 8/3/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#include "stdafx.h"
#include "AIPaddle.h"
#include "PlayScreen.h"
#include "GameBall.h"

void AIPaddle::HandleInput()
{
    const GameBall* gameBall = static_cast<GameBall*>
    (PlayScreen::GameObjects()->Get("Ball"));

    sf::Vector2f ballPosition = gameBall->GetPosition();

    if(GetPosition().x - 20 < ballPosition.x)
        _velocity += 15.0f;
    else if(GetPosition().x + 20 > ballPosition.x)
        _velocity -= 15.0f;
    else
        _velocity = 0.0f;
}