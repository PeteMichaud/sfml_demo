//
//  SoundFileCache.h
//  SideScroller
//
//  Created by Pete Michaud on 8/4/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#pragma once
#include "stdafx.h"

class SoundFileCache
{
public:
    SoundFileCache(void);
    ~SoundFileCache(void);

    sf::Sound GetSound(std::string) const;
    sf::Music* GetSong(std::string) const;

private:
    static std::map<std::string, sf::SoundBuffer*> _sounds;
    static std::map<std::string, sf::Music*> _music;

    template <typename T>
        struct Deallocator{
            void operator()(const std::pair<std::string,T> &p)
            {
                delete p.second;
            }
    };

};

class SoundNotFoundException : public std::runtime_error
{
public:
    SoundNotFoundException(std::string const& msg):
    std::runtime_error(msg)
    {}
};