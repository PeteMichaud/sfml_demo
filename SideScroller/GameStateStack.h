//
//  GameStateStack.h
//  SideScroller
//
//  Created by Pete Michaud on 8/17/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#pragma once
#include "GameState.h"

class GameStateStack
{
public:
    GameStateStack();
    ~GameStateStack();

    void Push(GameState* state);
    GameState* Peek();
    GameState* Pop();
    void Clear();
    int Count();
    
private:
    std::list<GameState*> _states;
    struct GameStateDeallocator
    {
        void operator()(const GameState* s) const
        {
            delete s;
        }
    };
};