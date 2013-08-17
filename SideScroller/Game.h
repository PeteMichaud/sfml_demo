//
//  Game.h
//  SideScroller
//
//  Created by Pete Michaud on 8/2/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#pragma once
#include "stdafx.h"
#include "PlayScreen.h"

class Game {

public:
    static void Start();
    static sf::RenderWindow& GetWindow();
    const static int SCREEN_WIDTH = 1024;
    const static int SCREEN_HEIGHT = 768;
    
private:
    static bool IsExiting();
    static void GameLoop();

    static void ShowSplashScreen();
    static void ShowMenu();

    enum GameState {
        Uninitialized,
        ShowingSplash,
        Paused,
        ShowingMenu,
        Playing,
        Exiting
    };

    static GameState _gameState;
    static sf::RenderWindow _mainWindow;
    static PlayScreen _playScreen;
};