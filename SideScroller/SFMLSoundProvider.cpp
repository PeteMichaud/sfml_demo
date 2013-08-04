//
//  SFMLSoundProvider.cpp
//  SideScroller
//
//  Created by Pete Michaud on 8/4/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#include "stdafx.h"
#include "SFMLSoundProvider.h"
#include "SoundFileCache.h"

SFMLSoundProvider::SFMLSoundProvider() :
_currentSongName("")
{
}

void SFMLSoundProvider::PlaySound(std::string filename)
{
    int availableChannel = -1;
    for(int i = 0; i < MAX_SOUND_CHANNELS; i++)
    {
        if(_currentSounds[i].getStatus() != sf::Sound::Playing)
        {
            availableChannel = i;
            break;
        }
    }

    if(availableChannel != -1)
    {
        try
        {
            _currentSounds[availableChannel] = _soundFileCache.GetSound(filename);
            _currentSounds[availableChannel].play();
        }
        catch(SoundNotFoundException& snfe)
        {
            //do nothing
        }
    }
}

void SFMLSoundProvider::PlaySong(std::string filename, bool looping)
{
    sf::Music * currentSong;
    try
    {
        currentSong = _soundFileCache.GetSong(filename);
    }
    catch(SoundNotFoundException&)
    {
        //can't find song, so exit
        return;
    }

    if (_currentSongName != "")
    {
        try
        {
            sf::Music* priorSong = _soundFileCache.GetSong(_currentSongName);
            if(priorSong->getStatus() != sf::Sound::Stopped)
            {
                priorSong->stop();
            }
        }
        catch(SoundNotFoundException&)
        {
            //previous song not located, no big deal
        }
    }

    _currentSongName = filename;
    currentSong->setLoop(looping);
    currentSong->play();
}

void SFMLSoundProvider::StopAllSounds()
{
    for(int i = 0; i < MAX_SOUND_CHANNELS; i++)
    {
        _currentSounds[i].stop();
    }

    if(_currentSongName != "")
    {
        sf::Music * currentSong = _soundFileCache.GetSong(_currentSongName);
        if (currentSong->getStatus() == sf::Sound::Playing)
        {
            currentSong->stop();
        }
    }

}

bool SFMLSoundProvider::IsSoundPlaying()
{
    for(int i = 0; i < MAX_SOUND_CHANNELS; i++)
    {
        if(_currentSounds[i].getStatus() == sf::Sound::Playing)
        {
            return true;
        }
    }
    return false;
}

bool SFMLSoundProvider::IsSongPlaying()
{
    if(_currentSongName != "")
    {
        return _soundFileCache.GetSong(_currentSongName)->getStatus() == sf::Music::Playing;
    }
    return false;
}
