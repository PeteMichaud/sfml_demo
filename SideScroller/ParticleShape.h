//
//  ParticleShape.h
//  SideScroller
//
//  Created by Pete Michaud on 8/16/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#pragma once
#include "stdafx.h"
#include "Particle.h"

namespace Particles
{
    class ParticleShape
    {
    public:
        ParticleShape(sf::Drawable* _shape);
        ~ParticleShape();
        virtual sf::Drawable* MutateShape(Particles::Particle* p) = 0;
        virtual void Update(Particles::Particle* p, float deltaTime) = 0;
        virtual void Reset(Particles::Particle* p) = 0;
        virtual Particles::Particle* Create(float radius) = 0;

    protected:
        sf::Drawable* _shape;
        template <typename T>
        T GetShape()
        {
            return (T)(_shape);
        }
    };
}