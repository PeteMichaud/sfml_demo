//
//  PlayScreen.h
//  SideScroller
//
//  Created by Pete Michaud on 8/17/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#pragma once
#include "stdafx.h"
#include "GameState.h"
#include "Camera.h"
#include "GameObjectManager.h"

class PlayScreen :
    public GameState
{
public:
    PlayScreen(sf::RenderWindow* rw);
    ~PlayScreen();
    void Loop();
    void Initialize();
    static Camera& GetCamera();
    static GameObjectManager* GameObjects();


private:
    static Camera _camera;
    static GameObjectManager _gameObjectManager;
    
};