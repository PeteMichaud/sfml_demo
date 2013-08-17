//
//  Particle.h
//  SideScroller
//
//  Created by Pete Michaud on 8/16/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#pragma once
#include "stdafx.h"
namespace Particles
{
    struct Particle
    {
        float _lifeSpan;
        float _age;
        uint8_t _alpha;
        sf::Transform _translation;
        sf::Transform _rotation;
        sf::Vector2f _velocity;
        sf::Vector2f _accel;
        bool _alive;

        Particle(float lifeSpan,
                 float age,
                 uint8_t alpha,
                 float angle,
                 sf::Vector2f position,
                 sf::Vector2f velocity,
                 sf::Vector2f accel) :
        _lifeSpan(lifeSpan),
        _velocity(velocity),
        _accel(accel),
        _age(age),
        _alpha(alpha),
        _alive(false)
        {
            _translation.translate(position);
            _rotation.rotate(angle);
        }

        void move(sf::Vector2f offset)
        {
            _translation.translate(offset);
        }

        void rotate(float angle)
        {
            _rotation.rotate(angle);
        }
    };
}