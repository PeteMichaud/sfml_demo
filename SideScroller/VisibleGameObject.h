//
//  VisibleGameObject.h
//  SideScroller
//
//  Created by Pete Michaud on 8/3/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#pragma once
#include "stdafx.h"

class VisibleGameObject
{
public:
    VisibleGameObject();
    virtual ~VisibleGameObject();

    virtual void Load(std::string filename);
    virtual void Draw(sf::RenderWindow & window);
    virtual void Update(float elapsedTime);

    virtual void SetPosition(float x, float y);
    virtual sf::Vector2f GetPosition() const;
    virtual bool IsLoaded() const;

    virtual float GetWidth() const;
    virtual float GetHeight() const;

    virtual sf::FloatRect GetBoundingRect() const;

protected:
    sf::Sprite& GetSprite();

private:
    sf::Sprite _sprite;
    sf::Texture _texture;
    std::string _fileName;
    bool _isLoaded;
};