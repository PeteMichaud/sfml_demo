//
//  ParticleShape.cpp
//  SideScroller
//
//  Created by Pete Michaud on 8/16/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#include "ParticleShape.h"
namespace Particles {
    ParticleShape::ParticleShape() { }

    ParticleShape::ParticleShape(sf::Drawable* shape)
    : _shape(shape) { }

    ParticleShape::~ParticleShape()
    {
        delete _shape;
    }
}