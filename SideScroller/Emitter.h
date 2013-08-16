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
        sf::Vector2f _position;
        sf::Vector2f _velocity;
        sf::Vector2f _accel;
        float _angle;
        bool _alive;
        
        Particle(float lifeSpan,
                 float age,
                 sf::Color color,
                 float angle,
                 sf::Vector2f position,
                 sf::Vector2f velocity,
                 sf::Vector2f accel) :
            _lifeSpan(lifeSpan),
            _position(position),
            _velocity(velocity),
            _accel(accel),
            _angle(angle),
            _age(age),
            _color(color),
            _alive(false)
        {
            _transform.translate(position);
            _transform.rotate(angle);
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
        }
    };

    sf::Shape& MutateShape(Emitter::Particle* p);

    struct ParticleDeallocator
    {
        void operator()(const Emitter::Particle* p) const
        {
            delete p;
        }
    };

private:
    Emitter::Particle* GetFirstDead();
    sf::RectangleShape _shape;
    sf::Transform _emitterTransform;
    std::vector<Emitter::Particle*> _particles;
    std::vector<Emitter::Particle*>::iterator _it;
    sf::Clock _clock;
    float _emitInterval;
    float _elapsedTime;
    float _lastEmissionTime;
};