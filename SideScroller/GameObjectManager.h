//
//  GameObjectManager.h
//  SideScroller
//
//  Created by Pete Michaud on 8/3/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#pragma once
#include "VisibleGameObject.h"

class GameObjectManager
{
public:
    GameObjectManager();
    ~GameObjectManager();

    void Add(std::string name, VisibleGameObject* gameObject);
    void Remove(std::string name);
    int GetObjectCount() const;
    VisibleGameObject* Get(std::string name) const;

    void DrawAll(sf::RenderWindow& renderWindow);
    void UpdateAll();
    
private:
    std::map<std::string, VisibleGameObject*> _gameObjects;
    sf::Clock clock;
    struct GameObjectDeallocator
    {
        void operator()(const std::pair<std::string, VisibleGameObject*> & p) const
        {
            delete p.second;
        }
    };
};