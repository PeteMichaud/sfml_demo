//
//  SplashScreen.cpp
//  SideScroller
//
//  Created by Pete Michaud on 8/3/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#include "stdafx.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "Game.h"

SplashScreen::SplashScreen(sf::RenderWindow* rw) :
GameState(rw)
{

}

void SplashScreen::Initialize()
{
    if(!_texture.loadFromFile(resourcePath("SplashScreen.png")))
        throw "Could not Load Screen image";
    _sprite.setTexture(_texture);
}

void SplashScreen::Loop()
{
    ServiceLocator::GetAudio()->PlaySong("nice_music.ogg", true);

    _rw->draw(_sprite);
    _rw->display();

    sf::Event event;

    while(true)
    {
        while(_rw->pollEvent(event))
        {
            if(event.type == sf::Event::EventType::KeyPressed
            || event.type == sf::Event::EventType::MouseButtonPressed
            || event.type == sf::Event::EventType::Closed)
            {
                Game::StateStack()->Pop();
                Game::StateStack()->Push(new MainMenu(_rw));
                return;
            }
        }
    }
}