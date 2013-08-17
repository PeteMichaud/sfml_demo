//
//  RectangleParticle.cpp
//  SideScroller
//
//  Created by Pete Michaud on 8/16/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#include "RectangleParticle.h"
#include "mathhelpers.h"

namespace Particles {
    RectangleParticle::RectangleParticle(sf::Drawable* shape) : Particles::ParticleShape(shape),
        _color(sf::Color::Yellow) { }

    sf::Drawable* RectangleParticle::MutateShape(Particles::Particle* p)
    {
        GetShape<sf::RectangleShape*>()->setFillColor(
            sf::Color(_color.r,_color.g, _color.b, p->_alpha));
        return GetShape<sf::RectangleShape*>();
    }

    void RectangleParticle::Update(Particles::Particle *p, float deltaTime)
    {
        p->_velocity += p->_accel * deltaTime;
        p->move(p->_velocity * deltaTime);
        p->rotate(36.0f * deltaTime);
        p->_alpha = ((p->_lifeSpan - p->_age) / p->_lifeSpan) * 255;
        p->_age += deltaTime;
    }

    Particles::Particle* RectangleParticle::Create(float radius)
    {
        return new Particle(
             5.0f, //lifespan
             6.0f, //age
             255, //alpha
             randf(360.0f), //angle
             sf::Vector2f(randf(-radius,radius),randf(-radius,radius)),
             sf::Vector2f(randf(-10.0f,10.0f),randf(-10.0f,10.0f)),
             sf::Vector2f(randf(-10.0f,10.0f),randf(-10.0f,10.0f))
        );
    }

    void RectangleParticle::Reset(Particles::Particle *p)
    {
        p->_alpha = 255;
        p->_translation = sf::Transform();
        p->_rotation = sf::Transform();
        p->move(sf::Vector2f(randf(-50.0f,50.0f),randf(-50.0f,50.0f)));
        p->rotate(randf(360.0f));
        p->_velocity = sf::Vector2f(randf(-10.0f,10.0f),randf(-10.0f,10.0f));
        p->_accel = sf::Vector2f(randf(-10.0f,10.0f),randf(-10.0f,10.0f));
        p->_age = 0.0f;
        p->_alive = true;
    }
}