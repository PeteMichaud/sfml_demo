//
//  GameObjectManager.cpp
//  SideScroller
//
//  Created by Pete Michaud on 8/3/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#include "stdafx.h"
#include "GameObjectManager.h"
#include "Game.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
    std::for_each(
                  _gameObjects.begin(),
                  _gameObjects.end(),
                  GameObjectDeallocator());
}

void GameObjectManager::Add(std::string name, VisibleGameObject* gameObject)
{
    _gameObjects.insert(
        std::pair<std::string, VisibleGameObject*>(name, gameObject));
}

void GameObjectManager::Remove(std::string name)
{
    std::map<std::string, VisibleGameObject*>::iterator results =
        _gameObjects.find(name);
    if (results != _gameObjects.end())
    {
        delete results->second;
        _gameObjects.erase(results);
    }
}

VisibleGameObject* GameObjectManager::Get(std::string name) const
{
    std::map<std::string, VisibleGameObject*>::const_iterator results =
        _gameObjects.find(name);
    if (results == _gameObjects.end())
        return NULL;
    return results->second;
}

int GameObjectManager::GetObjectCount() const
{
    return _gameObjects.size();
}

void GameObjectManager::DrawAll(sf::RenderWindow& renderWindow)
{
    std::map<std::string,VisibleGameObject*>::const_iterator itr =
        _gameObjects.begin();
    for(;itr != _gameObjects.end();itr++)
    {
        itr->second->Draw(renderWindow);
    }
}

void GameObjectManager::UpdateAll()
{

    std::map<std::string,VisibleGameObject*>::const_iterator itr =
        _gameObjects.begin();

    //remove dead objects
    for(; itr != _gameObjects.end(); )
    {
        if (itr->second->IsDead())
        {
            itr = _gameObjects.erase(itr++);
        }
        else
        {
            ++itr;
        }
    }

    itr = _gameObjects.begin();

    float timeDelta = clock.restart().asSeconds();

    for(;itr != _gameObjects.end();itr++)
    {
        itr->second->Update(timeDelta);
    }
}