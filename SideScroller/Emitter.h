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
        float _angle;
        sf::Vector2f _position;
        sf::Vector2f _velocity;
        sf::Vector2f _accel;
        sf::CircleShape _shape;
        bool _alive;
        
        Particle(float lifeSpan,
                 float age,
                 sf::Color color,
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
            _shape.setRadius(10.0f);
            _shape.setPosition(position);
            _shape.setFillColor(_color);
        }

        void move(sf::Vector2f offset)
        {
            _shape.move(offset);
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
        
    sf::Vector2f _position;
    std::vector<Emitter::Particle*> _particles;
    std::vector<Emitter::Particle*>::iterator _it;
    sf::Clock _clock;
    float _emitInterval;
    float _elapsedTime;
    float _lastEmissionTime;
};