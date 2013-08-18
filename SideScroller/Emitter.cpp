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
#include "stringhelpers.h"

namespace Particles
{

    Emitter::Emitter(ParticleShape* shape, sf::Vector2f position, int particleCount, float emitInterval, int dieAfter):
    _emitInterval(emitInterval),
    _shape(shape),
    _elapsedTime(0.0f),
    _lastEmissionTime(0.0f),
    _radius(0.0f),
    _particlesEmitted(0),
    _dieAfter(dieAfter)
    {
        _emitterTransform.translate(position);
        for(int i = 0; i < particleCount; i++)
        {
            _particles.push_back(_shape->Create(_radius));
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
            if ((*_it)->_alive)
            {
                if ((*_it)->_age > (*_it)->_lifeSpan)
                {
                    (*_it)->_alive = false;
                }
                else
                {
                    _shape->Update(*_it, deltaTime);
                }
            }
        }

        //emit new particles if it's time
        if (!EmissionComplete())
        {
            if(_elapsedTime >= _lastEmissionTime+_emitInterval)
            {
                Particles::Particle* p = GetFirstDead();
                if (p != NULL)
                {
                    _shape->Reset(p);
                    _lastEmissionTime = _elapsedTime;
                    _particlesEmitted++;
                }
            }
        }
    }

    void Emitter::Draw(sf::RenderWindow &rw)
    {
        for(_it = _particles.begin(); _it != _particles.end();_it++)
        {
            if ((*_it)->_alive)
            {
                rw.draw(
                    *_shape->MutateShape(*_it),
                    _emitterTransform * (*_it)->_translation * (*_it)->_rotation);
            }
        }
    }

    void Emitter::Move(sf::Vector2f delta)
    {
        _emitterTransform.translate(delta);
    }

    Particles::Particle* Emitter::GetFirstDead()
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

    bool Emitter::EmissionComplete() const
    {
        return _particlesEmitted > _dieAfter && _dieAfter > 0;
    }

    bool Emitter::IsDead() const
    {
        return EmissionComplete() && AllParticlesDead();
    }

    bool Emitter::AllParticlesDead() const
    {
        return std::find_if(
            _particles.begin(),
            _particles.end(),
            [](Particles::Particle* p) { return p->_alive; })
        == _particles.end();
    }
}