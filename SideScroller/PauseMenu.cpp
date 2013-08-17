//
//  PauseMenu.cpp
//  SideScroller
//
//  Created by Pete Michaud on 8/3/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#include "stdafx.h"
#include "PauseMenu.h"
#include "Game.h"

PauseMenu::PauseMenu(sf::RenderWindow* rw) :
    GameState(rw)
{

}

void PauseMenu::Initialize()
{
    if(!_texture.loadFromFile(resourcePath("MainMenu.png")))
        throw "Could not load menu texture";
    _sprite.setTexture(_texture);

    MenuItem playButton;
    playButton.rect.top     = 145;
    playButton.rect.height  = 235;
    playButton.rect.left    = 0;
    playButton.rect.width   = 1023;
    playButton.action       = Play;

    MenuItem exitButton;
    exitButton.rect.top     = 0;
    exitButton.rect.height  = 1023;
    exitButton.rect.left    = 383;
    exitButton.rect.width   = 177;
    exitButton.action       = Exit;

    _menuItems.push_back(playButton);
    _menuItems.push_back(exitButton);
}

void PauseMenu::Loop()
{
    _rw->draw(_sprite);
    _rw->display();

    switch(GetMenuResponse(*_rw))
    {
        case PauseMenu::Exit:
            Game::StateStack()->Clear();
            break;
        case PauseMenu::Play:
            Game::StateStack()->Pop();
            break;
        case PauseMenu::Nothing:
            break;
    }
}

PauseMenu::MenuResult PauseMenu::HandleClick(int x, int y)
{
    std::list<MenuItem>::iterator it;
    for(it = _menuItems.begin(); it != _menuItems.end(); it++)
    {
        sf::Rect<int> menuItemRect = (*it).rect;
        if (menuItemRect.top + menuItemRect.height > y
            && menuItemRect.top < y
            && menuItemRect.left < x
            && menuItemRect.left + menuItemRect.width > x)
        {
            return (*it).action;
        }
    }

    return Nothing;
}

PauseMenu::MenuResult PauseMenu::GetMenuResponse(sf::RenderWindow& window)
{
    sf::Event menuEvent;
    while(true)
    {
        while(window.pollEvent(menuEvent))
        {
            if (menuEvent.type == sf::Event::MouseButtonPressed)
            {
                if(ServiceLocator::GetAudio()->IsSongPlaying())
                {
                    ServiceLocator::GetAudio()->StopAllSounds();
                    ServiceLocator::GetAudio()->PlaySong("play_music.wav", true);
                }
                return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
            }
            if (menuEvent.type == sf::Event::Closed)
            {
                return Exit;
            }
        }
    }
}