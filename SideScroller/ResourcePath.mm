////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2013 Marco Antognini (antognini.marco@gmail.com), 
//                         Laurent Gomila (laurent.gom@gmail.com), 
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "ResourcePath.hpp"
#import <Foundation/Foundation.h>

std::vector<std::string> imageExtensions {"jpg", "png"};
std::vector<std::string> soundExtensions {"ogg", "mp3", "wav"};
std::vector<std::string> shaderExtensions {"vert", "frag"};
std::vector<std::string> fontExtensions{"ttf"};

////////////////////////////////////////////////////////////
std::string resourcePath(void)
{
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    
    std::string rpath;
    NSBundle* bundle = [NSBundle mainBundle];
    
    if (bundle == nil) {
#ifdef DEBUG
        NSLog(@"bundle is nil... thus no resources path can be found.");
#endif
    } else {
        NSString* path = [bundle resourcePath];
        rpath = [path UTF8String] + std::string("/");
    }
    
    [pool drain];
    
    return rpath;
}

std::string resourcePath(std::string fileName)
{
    std::string folder = getFolder(fileName);
    return resourcePath() + "Resources/" + folder + fileName;
}

std::string getFolder(const std::string& fileName)
{
    std::string ext = getExtension(fileName);

    if(vector_contains(&imageExtensions, ext))
        return "Images/";
    else if(vector_contains(&soundExtensions, ext))
        return "Sounds/";
    else if(vector_contains(&shaderExtensions, ext))
        return "Shaders/";
    else if(vector_contains(&fontExtensions, ext))
        return "Fonts/";
    else
        return "";
}

std::string getExtension(const std::string& fileName)
{
    std::string::size_type idx;

    idx = fileName.rfind('.');

    if(idx != std::string::npos)
    {
        return fileName.substr(idx+1);
    }
    else
    {
        return "";
    }
}

bool vector_contains(std::vector<std::string>* v, std::string value)
{
    return std::find(v->begin(), v->end(), value) != v->end();
}