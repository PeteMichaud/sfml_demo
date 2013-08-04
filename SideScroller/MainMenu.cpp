//
//  MainMenu.cpp
//  SideScroller
//
//  Created by Pete Michaud on 8/3/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#include "stdafx.h"
#include "MainMenu.h"

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{
    sf::Texture texture;
    texture.loadFromFile(resourcePath("mainMenu.png"));
    sf::Sprite sprite(texture);

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

    window.draw(sprite);
    window.display();

    return GetMenuResponse(window);
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
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

MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
    sf::Event menuEvent;
    while(true)
    {
        while(window.pollEvent(menuEvent))
        {
            if (menuEvent.type == sf::Event::MouseButtonPressed)
            {
                return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
            }
            if (menuEvent.type == sf::Event::Closed)
            {
                return Exit;
            }
        }
    }
}