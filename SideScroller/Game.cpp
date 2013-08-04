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
#include "MainMenu.h"

void Game::Start(void)
{
    if (_gameState != Uninitialized)
        return;

    _mainWindow.create(sf::VideoMode(1024,768,32), "Pang!");
    //_mainWindow.setFramerateLimit(60);

    PlayerPaddle *player1 = new PlayerPaddle();
    player1->SetPosition(SCREEN_WIDTH/2, 700);

    GameBall *ball = new GameBall();
    ball->SetPosition(SCREEN_WIDTH/2, (SCREEN_HEIGHT/2)-15);

    _gameObjectManager.Add("Paddle1",player1);
    _gameObjectManager.Add("Ball", ball);

    _gameState = Game::ShowingSplash;

    while(!IsExiting())
    {
        GameLoop();
    }

    _mainWindow.close();
}

bool Game::IsExiting()
{
    if (_gameState == Game::Exiting)
        return true;
    else
        return false;
}

sf::RenderWindow& Game::GetWindow()
{
    return _mainWindow;
}

sf::Event Game::CurrentEvent()
{
    return _currentEvent;
}

GameObjectManager Game::GameObjects()
{
    return _gameObjectManager;
}

void Game::GameLoop()
{
    while(_mainWindow.pollEvent(_currentEvent))
    {
        switch (_gameState) {
            case Game::ShowingMenu:
            {
                ShowMenu();
                break;
            }
            case Game::ShowingSplash:
            {
                ShowSplashScreen();
                break;
            }
            case Game::Playing:
            {
                _mainWindow.clear(sf::Color(255,0,0));

                _gameObjectManager.UpdateAll(_clock.restart().asSeconds());
                _gameObjectManager.DrawAll(_mainWindow);
                _mainWindow.display();

                if(_currentEvent.type == sf::Event::Closed)
                {
                    _gameState = Game::Exiting;
                }

                if(_currentEvent.type == sf::Event::KeyPressed)
                {
                    if(_currentEvent.key.code == sf::Keyboard::Escape) ShowMenu();
                }
                
                break;
            }
            case Game::Uninitialized:
            case Game::Exiting:
            case Game::Paused:
                break;
        }
    }
}

void Game::ShowSplashScreen()
{
    SplashScreen splashScreen;
    splashScreen.Show(_mainWindow);
    _gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
    MainMenu mainMenu;
    MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
    switch(result)
    {
        case MainMenu::Exit:
            _gameState = Game::Exiting;
            break;
        case MainMenu::Play:
            _gameState = Game::Playing;
            break;
        case MainMenu::Nothing:
            break;
    }
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;
sf::Clock Game::_clock;
sf::Event Game::_currentEvent;
