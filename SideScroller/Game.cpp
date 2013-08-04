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

    _mainWindow.create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32), "Pang!");
    //_mainWindow.setFramerateLimit(60);

    SFMLSoundProvider soundProvider;
    ServiceLocator::RegisterServiceLocator(&soundProvider);
    ServiceLocator::GetAudio()->PlaySong("nice_music.ogg", true);
    
    PlayerPaddle* player1 = new PlayerPaddle();
    player1->SetPosition(SCREEN_WIDTH/2, 700);

    AIPaddle* player2 = new AIPaddle();
    player2->SetPosition(SCREEN_WIDTH/2, 40);

    GameBall *ball = new GameBall();
    ball->SetPosition(SCREEN_WIDTH/2, (SCREEN_HEIGHT/2)-15);

    _gameObjectManager.Add("Paddle1", player1);
    _gameObjectManager.Add("Paddle2", player2);
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
    return _gameState == Game::Exiting;
}

sf::RenderWindow& Game::GetWindow()
{
    return _mainWindow;
}

const GameObjectManager& Game::GameObjects()
{
    return Game::_gameObjectManager;
}

void Game::GameLoop()
{
    sf::Event currentEvent;
    _mainWindow.pollEvent(currentEvent);
    
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
                _mainWindow.clear(sf::Color(0,0,0));

                _gameObjectManager.UpdateAll();
                _gameObjectManager.DrawAll(_mainWindow);
                _mainWindow.display();

                if(currentEvent.type == sf::Event::Closed)
                {
                    _gameState = Game::Exiting;
                }

                if(currentEvent.type == sf::Event::KeyPressed)
                {
                    if(currentEvent.key.code == sf::Keyboard::Escape) ShowMenu();
                }
                
                break;
            }
            case Game::Uninitialized:
            case Game::Exiting:
            case Game::Paused:
                break;
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