//
//  IAudioProvider.h
//  SideScroller
//
//  Created by Pete Michaud on 8/4/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#pragma once
#include "stdafx.h"

class IAudioProvider
{
public:
    virtual ~IAudioProvider() {}
    virtual void PlaySound(std::string filename) = 0;
    virtual void PlaySong(std::string filename, bool looping) = 0;
    virtual void StopAllSounds() = 0;

    virtual bool IsSoundPlaying() = 0;
    virtual bool IsSongPlaying() = 0;
};