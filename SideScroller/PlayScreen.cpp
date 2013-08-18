//
//  PlayScreen.cpp
//  SideScroller
//
//  Created by Pete Michaud on 8/17/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#include "PlayScreen.h"
#include "PlayerPaddle.h"
#include "AIPaddle.h"
#include "GameBall.h"
#include "Emitter.h"
#include "RectangleParticle.h"
#include "PauseMenu.h"

PlayScreen::PlayScreen(sf::RenderWindow* rw) :
    GameState(rw),
    _totalTime(0.0f)
{
    
}

PlayScreen::~PlayScreen()
{
    
}

void PlayScreen::Initialize()
{
    PlayerPaddle* player1 = new PlayerPaddle();
    player1->SetPosition(Game::SCREEN_WIDTH/2, 700);

    AIPaddle* player2 = new AIPaddle();
    player2->SetPosition(Game::SCREEN_WIDTH/2, 40);

    GameBall* ball = new GameBall();

    _gameObjectManager.Add("Paddle1", player1);
    _gameObjectManager.Add("Paddle2", player2);
    _gameObjectManager.Add("Ball", ball);

    _backgroundTexture.loadFromFile(resourcePath("play_back.png"));
    _backgroundSprite.setTexture(_backgroundTexture);


    _backgroundShader.loadFromFile(
                               resourcePath("ripple.vert"),
                               resourcePath("ripple.frag"));
    _backgroundShader.setParameter("tex0", sf::Shader::CurrentTexture);
    _backgroundShader.setParameter("resolution", sf::Vector2f(1024.0f,768.0f));
    

}

void PlayScreen::Loop()
{
    _totalTime += _clock.restart().asSeconds();

    _camera.Update();
    _rw->setView(_camera.GetView());

    _backgroundShader.setParameter("time", _totalTime);
    std::cout << _totalTime << " \n";
    _rw->draw(_backgroundSprite, &_backgroundShader
              );
    
    _gameObjectManager.UpdateAll();
    _gameObjectManager.DrawAll(*_rw);


    _rw->display();

    sf::Event currentEvent;
    if(_rw->pollEvent(currentEvent))
    {
        if(currentEvent.type == sf::Event::Closed)
        {
            Game::StateStack()->Clear();
        }

        if(currentEvent.type == sf::Event::KeyPressed)
        {
            if(currentEvent.key.code == sf::Keyboard::Escape)
            {
                Game::StateStack()->Push(new PauseMenu(_rw));
            }
        }
    }
}

Camera& PlayScreen::GetCamera()
{
    return _camera;
}

GameObjectManager* PlayScreen::GameObjects()
{
    return &PlayScreen::_gameObjectManager;
}

GameObjectManager PlayScreen::_gameObjectManager;
Camera PlayScreen::_camera;