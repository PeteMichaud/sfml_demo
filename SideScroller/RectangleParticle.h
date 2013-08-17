//
//  RectangleParticle.h
//  SideScroller
//
//  Created by Pete Michaud on 8/16/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#pragma once
#include "stdafx.h"
#include "ParticleShape.h"

namespace Particles {
    class RectangleParticle :
        public ParticleShape
    {
    public:
        RectangleParticle(sf::Drawable* shape);
        sf::Drawable* MutateShape(Particles::Particle* p);
        void Update(Particles::Particle* p, float deltaTime);
        void Reset(Particles::Particle* p);
        Particles::Particle* Create(float radius);

        sf::Color _color;
    };
}