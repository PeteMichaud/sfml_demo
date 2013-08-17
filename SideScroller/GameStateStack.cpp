//
//  GameStateStack.cpp
//  SideScroller
//
//  Created by Pete Michaud on 8/17/13.
//  Copyright (c) 2013 Pete Michaud. All rights reserved.
//

#include "GameStateStack.h"

GameStateStack::GameStateStack()
{
}

GameStateStack::~GameStateStack()
{
    std::for_each(
                  _states.begin(),
                  _states.end(),
                  GameStateDeallocator());
}

void GameStateStack::Push(GameState *state)
{
    state->Initialize();
    _states.push_back(state);
}

GameState* GameStateStack::Pop()
{
    GameState* state = GameStateStack::Peek();
    _states.pop_back();
    return state;
}

GameState* GameStateStack::Peek()
{
    return _states.back();
}

void GameStateStack::Clear()
{
    _states.clear();
}

int GameStateStack::Count()
{
    return _states.size();
}