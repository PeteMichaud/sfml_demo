//
//  stringhelpers.h
//  SideScroller
//
//  Created by Pete Michaud on 8/5/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#include <iostream>
#include <sstream>
using namespace std;

template <typename T>
inline string to_s(T val)
{
    stringstream ss(stringstream::in | stringstream::out);
    ss << val;
    return ss.str();
}

template <typename T>
inline string zero_pad(T val, int padding = 8)
{
    stringstream ss;

    ss << val;

    string padded;

    ss >> padded;

    int strLength = padded.length();
    for(int i = 0; i < padding - strLength; i++)
        padded = "0" + padded;

    return padded;
}

