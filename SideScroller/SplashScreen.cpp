//
//  SplashScreen.cpp
//  SideScroller
//
//  Created by Pete Michaud on 8/3/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#include "stdafx.h"
#include "SplashScreen.h"

void SplashScreen::Show(sf::RenderWindow & renderWindow)
{
    sf::Texture texture;
    if(!texture.loadFromFile(resourcePath("SplashScreen.png")))
        return;

    ServiceLocator::GetAudio()->PlaySong("nice_music.ogg", true);

    sf::Sprite sprite;
    sprite.setTexture(texture);

    renderWindow.draw(sprite);
    renderWindow.display();

    sf::Event event;

    while(true)
    {
        while(renderWindow.pollEvent(event))
        {
            if(event.type == sf::Event::EventType::KeyPressed
            || event.type == sf::Event::EventType::MouseButtonPressed
            || event.type == sf::Event::EventType::Closed)
            {
                return;
            }
        }
    }
}