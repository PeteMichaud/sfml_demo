//
//  Spark.cpp
//  SideScroller
//
//  Created by Pete Michaud on 8/16/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#include "Spark.h"
#include "mathhelpers.h"

namespace Particles {
    Spark::Spark(sf::Vector2f direction) :
        _color(sf::Color::Yellow),
        _direction(direction*40.0f)
    {
        sf::RectangleShape* r = new sf::RectangleShape();

        r->setSize(sf::Vector2f(2.0f, 8.0f));
        r->setOrigin(r->getSize().x/2,r->getSize().y/2);

        _shape = r;
    }

    sf::Drawable* Spark::MutateShape(Particles::Particle* p)
    {
        GetShape<sf::RectangleShape*>()->setFillColor(
            sf::Color(_color.r,_color.g, _color.b, p->_alpha));
        return GetShape<sf::RectangleShape*>();
    }

    void Spark::Update(Particles::Particle *p, float deltaTime)
    {
        p->_velocity += p->_accel * deltaTime;
        p->move(p->_velocity * deltaTime);
        p->rotate(0.5f);
        p->_alpha = ((p->_lifeSpan - p->_age) / p->_lifeSpan) * 255;
        p->_age += deltaTime;
    }

    Particles::Particle* Spark::Create(float radius)
    {
        return new Particle(
            0.5f, //lifespan
            1.0f, //age
            255, //alpha
            0.0f, //angle
            sf::Vector2f(15.0f*(_direction.x/std::abs(_direction.x)),0.0f),
            sf::Vector2f(0.0f, _direction.y),
            sf::Vector2f(0.0f, 0.0f)
            );
    }

    void Spark::Reset(Particles::Particle *p)
    {
        p->_alpha = 255;
        p->_translation = sf::Transform();
        p->_rotation = sf::Transform();
        p->move(sf::Vector2f(15.0f*(_direction.x/std::abs(_direction.x)),0.0f));
        //p->rotate(randf(360.0f));
        p->_velocity = sf::Vector2f(0.0f, _direction.y);
        p->_accel = sf::Vector2f(0.0f, 0.0f);
        p->_age = 0.0f;
        p->_alive = true;
    }
}