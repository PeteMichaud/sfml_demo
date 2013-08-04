//
//  SFMLSoundProvider.h
//  SideScroller
//
//  Created by Pete Michaud on 8/4/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#pragma once

#include "stdafx.h"
#include "IAudioProvider.h"

class SFMLSoundProvider : public IAudioProvider
{
public:

    SFMLSoundProvider();

    void PlaySound(std::string filename);
    void PlaySong(std::string filename, bool looping = false);
    void StopAllSounds();

    bool IsSoundPlaying();
    bool IsSongPlaying();

private:
    sf::SoundBuffer _soundBuffer;
    sf::Sound _sound;
    sf::Music _music;
};