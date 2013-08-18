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
    GameState(rw)
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

    sf::RectangleShape* r = new sf::RectangleShape();

    r->setSize(sf::Vector2f(5.0f, 5.0f));
    r->setOrigin(r->getSize().x/2,r->getSize().y/2);

    Particles::RectangleParticle* ps = new Particles::RectangleParticle(r);
    Particles::Emitter* pEmitter = new Particles::Emitter(ps, sf::Vector2f(512,384),  500, 0.1f);

    _gameObjectManager.Add("Paddle1", player1);
    _gameObjectManager.Add("Paddle2", player2);
    _gameObjectManager.Add("Ball", ball);
    _gameObjectManager.Add("Emitter", pEmitter);
}

void PlayScreen::Loop()
{
    _camera.Update();

    _rw->setView(_camera.GetView());
    _rw->clear(sf::Color(37,78,106));

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

const GameObjectManager* PlayScreen::GameObjects()
{
    return &PlayScreen::_gameObjectManager;
}

GameObjectManager PlayScreen::_gameObjectManager;
Camera PlayScreen::_camera;