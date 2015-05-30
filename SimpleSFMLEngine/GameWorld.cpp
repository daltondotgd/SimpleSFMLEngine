#include "stdafx.h"
#include "GameWorld.h"

#include "Player.h"
#include "FPSCounter.h"
#include "Engine.h"

GameWorld::GameWorld()
    : World()
{
}


GameWorld::~GameWorld()
{
}

void GameWorld::init()
{
    player = new Player();
    add(player);

#ifdef _DEBUG
    add(new FPSCounter(60));
#endif
}
