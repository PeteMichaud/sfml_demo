//
//  Game.cpp
//  SideScroller
//
//  Created by Pete Michaud on 8/2/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#include "stdafx.h"

#include "Game.h"
#include "SplashScreen.h"

void Game::Start(void)
{
    if (_gameStateStack.Count() > 0)
        return;

    _mainWindow.create(
        sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32),
        "Suicide Ball"
    );
    //_mainWindow.setFramerateLimit(60);

    SFMLSoundProvider soundProvider;
    ServiceLocator::RegisterServiceLocator(&soundProvider);

    _gameStateStack.Push(new SplashScreen(&_mainWindow));

    while(!IsExiting())
    {
        GameLoop();
    }

    _mainWindow.close();
}

bool Game::IsExiting()
{
    return _gameStateStack.Count() == 0;
}

void Game::GameLoop()
{
    _gameStateStack.Peek()->Loop();
}

GameStateStack* Game::StateStack()
{
    return &_gameStateStack;
}

sf::RenderWindow Game::_mainWindow;
GameStateStack Game::_gameStateStack;