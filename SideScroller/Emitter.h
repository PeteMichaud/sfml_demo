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
#include "Particle.h"
#include "ParticleShape.h"

namespace Particles {
    class Emitter :
        public VisibleGameObject {
    public:
            Emitter(ParticleShape* shape, sf::Vector2f position, int particleCount, float emitInterval);
        ~Emitter();
        void Update(float elapsedTime);
        void Draw(sf::RenderWindow& rw);

        void Move(sf::Vector2f delta);

        struct ParticleDeallocator
        {
            void operator()(const Particles::Particle* p) const
            {
                delete p;
            }
        };

    private:
        Particles::Particle* GetFirstDead();
        ParticleShape* _shape;
        sf::Transform _emitterTransform;
        std::vector<Particles::Particle*> _particles;
        std::vector<Particles::Particle*>::iterator _it;
        sf::Clock _clock;
        float _emitInterval;
        float _elapsedTime;
        float _lastEmissionTime;
        float _radius;
    };
}