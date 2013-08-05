//
//  VisibleGameObject.cpp
//  SideScroller
//
//  Created by Pete Michaud on 8/3/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#include "stdafx.h"
#include "VisibleGameObject.h"

VisibleGameObject::VisibleGameObject()
:_isLoaded(false)
{
}

VisibleGameObject::~VisibleGameObject()
{

}

void VisibleGameObject::Load(std::string filename)
{
    if(!_texture.loadFromFile(filename))
    {
        _fileName = "";
        _isLoaded = false;
    }
    else
    {
        _fileName = filename;
        _sprite.setTexture(_texture);
        _isLoaded = true;
    }
}

void VisibleGameObject::Draw(sf::RenderWindow & renderWindow)
{
    if (_isLoaded)
    {
        renderWindow.draw(_sprite);
    }
    renderWindow.draw(_rect);
}

void VisibleGameObject::Update(float elapsedTime)
{

}

void VisibleGameObject::SetPosition(float x, float y)
{
    if (_isLoaded)
    {
        _sprite.setPosition(x,y);
    }
    _rect.setPosition(x,y);
}

sf::Vector2f VisibleGameObject::GetPosition() const
{
    if (_isLoaded)
    {
        return _sprite.getPosition();
    }
    return _rect.getPosition();
}

sf::Sprite& VisibleGameObject::GetSprite()
{
    return _sprite;
}

sf::RectangleShape& VisibleGameObject::GetRect()
{
    return _rect;
}

float VisibleGameObject::GetHeight() const
{
    if (_isLoaded)
    {
        return _sprite.getGlobalBounds().height;
    }
    return _rect.getGlobalBounds().height;
}

float VisibleGameObject::GetWidth() const
{
    if (_isLoaded)
    {
        return _sprite.getGlobalBounds().width;
    }

    return _rect.getGlobalBounds().width;
}

sf::FloatRect VisibleGameObject::GetBoundingRect() const
{
    if (_isLoaded)
    {
        return _sprite.getGlobalBounds();
    }
    return _rect.getGlobalBounds();
}

bool VisibleGameObject::IsLoaded() const
{
    return _isLoaded;
}
