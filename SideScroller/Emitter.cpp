//
//  Emitter.cpp
//  SideScroller
//
//  Created by Pete Michaud on 8/8/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#include "Emitter.h"
#include "Game.h"
#include "mathhelpers.h"

Emitter::Emitter(int particleCount, float emitInterval):
_emitInterval(emitInterval),
_elapsedTime(0.0f),
_lastEmissionTime(0.0f)
{
    _transform.translate(Game::SCREEN_WIDTH/2,Game::SCREEN_HEIGHT/2);
    for(int i = 0; i < particleCount; i++)
    {
        _particles.push_back(new Particle(
            5.0f,
            6.0f,
            sf::Color::Cyan,
            randf(360.0f),
            sf::Vector2f(randf(-50.0f,50.0f),randf(-50.0f,50.0f)),
            sf::Vector2f(randf(-10.0f,10.0f),randf(-10.0f,10.0f)),
            sf::Vector2f(randf(-10.0f,10.0f),randf(-10.0f,10.0f))
        ));
    }
}

Emitter::~Emitter()
{
    std::for_each(
      _particles.begin(),
      _particles.end(),
      ParticleDeallocator());
}

void Emitter::Update(float deltaTime)
{
    _elapsedTime += deltaTime;

    //update all particles
    for(_it = _particles.begin(); _it != _particles.end();_it++)
    {
        //kill if too old
        if ((*_it)->_age > (*_it)->_lifeSpan)
        {
            (*_it)->_alive = false;
        }
        else
        {
            (*_it)->_velocity += (*_it)->_accel * deltaTime;
            (*_it)->move((*_it)->_velocity * deltaTime);
            (*_it)->rotate(36.0f * deltaTime);
            (*_it)->setAlpha(
                ((*_it)->_lifeSpan - (*_it)->_age) / (*_it)->_lifeSpan);
            (*_it)->_age += deltaTime;
        }
    }

    //emit new particles if it's time
    if (_elapsedTime >= _lastEmissionTime+_emitInterval)
    {
        Emitter::Particle* p = GetFirstDead();
        if (p != NULL)
        {
            p->_color = sf::Color::Cyan;
            p->_transform = sf::Transform();
            p->move(sf::Vector2f(randf(-50.0f,50.0f),randf(-50.0f,50.0f)));
            p->rotate(randf(360.0f));
            p->_velocity = sf::Vector2f(randf(-10.0f,10.0f),randf(-10.0f,10.0f));
            p->_accel = sf::Vector2f(randf(-10.0f,10.0f),randf(-10.0f,10.0f));
            p->_age = 0.0f;
            p->_alive = true;

            _lastEmissionTime = _elapsedTime;
        }
    }
}

void Emitter::Draw(sf::RenderWindow &rw)
{
    for(_it = _particles.begin(); _it != _particles.end();_it++)
    {
        if ((*_it)->_alive)
        {
            rw.draw((*_it)->_shape, _transform * (*_it)->_transform);
        }
    }
}

Emitter::Particle* Emitter::GetFirstDead()
{
    for(_it = _particles.begin(); _it != _particles.end();_it++)
    {
        if (!(*_it)->_alive)
        {
            return *_it;
        }
    }

    return NULL;
}