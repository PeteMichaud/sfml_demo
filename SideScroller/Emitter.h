//
//  Emitter.h
//  SideScroller
//
//  Created by Pete Michaud on 8/8/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"
#include "Game.h"

class Emitter :
    public VisibleGameObject {
public:
    Emitter(int particleCount, float emitInterval);
    ~Emitter();
    void Update(float elapsedTime);
    void Draw(sf::RenderWindow& rw);

    struct Particle
    {
        float _lifeSpan;
        float _age;
        sf::Color _color;
        sf::Transform _transform;
        sf::Vector2f _velocity;
        sf::Vector2f _accel;
        sf::RectangleShape _shape;
        bool _alive;
        
        Particle(float lifeSpan,
                 float age,
                 sf::Color color,
                 float angle,
                 sf::Vector2f position,
                 sf::Vector2f velocity,
                 sf::Vector2f accel) :
            _lifeSpan(lifeSpan),
            _velocity(velocity),
            _accel(accel),
            _age(age),
            _color(color),
            _alive(false)
        {
            _transform.translate(position);
            _transform.rotate(angle);
            _shape.setSize(sf::Vector2f(20.0f, 20.0f));
            _shape.setFillColor(_color);
            _shape.setOrigin(10,10);
        }

        void move(sf::Vector2f offset)
        {
            _transform.translate(offset);
        }

        void rotate(float angle)
        {
            _transform.rotate(angle);
        }

        void setAlpha(float a)
        {
            _color.a = a * 255;
            _shape.setFillColor(_color);
        }
    };

    struct ParticleDeallocator
    {
        void operator()(const Emitter::Particle* p) const
        {
            delete p;
        }
    };

private:
    Emitter::Particle* GetFirstDead();
    sf::Transform _transform;
    std::vector<Emitter::Particle*> _particles;
    std::vector<Emitter::Particle*>::iterator _it;
    sf::Clock _clock;
    float _emitInterval;
    float _elapsedTime;
    float _lastEmissionTime;
};