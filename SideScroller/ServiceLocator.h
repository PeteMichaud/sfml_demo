//
//  ServiceLocator.h
//  SideScroller
//
//  Created by Pete Michaud on 8/4/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#pragma once
#include "stdafx.h"
#include "IAudioProvider.h"

class ServiceLocator
{
public:
    static IAudioProvider* GetAudio() { return _audioProvider; } const
    static void RegisterServiceLocator(IAudioProvider *provider)
    {
        _audioProvider = provider;
    }
private:
    static IAudioProvider * _audioProvider;
};