//
//  MainMenu.h
//  SideScroller
//
//  Created by Pete Michaud on 8/3/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#pragma once
#include "stdafx.h"

class MainMenu
{
public:
    enum MenuResult { Nothing, Exit, Play };

    struct MenuItem
    {
    public:
        sf::Rect<int> rect;
        MenuResult action;
    };

    MenuResult Show(sf::RenderWindow& window);

private:
    MenuResult GetMenuResponse(sf::RenderWindow& window);
    MenuResult HandleClick(int x, int y);
    std::list<MenuItem> _menuItems;
};