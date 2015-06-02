#include "stdafx.h"
#include "GameWorld.h"

#include "Player.h"
#include "FPSCounter.h"
#include "Engine.h"
#include "HUD.h"

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

    getEngine().getCamera().zoom(.25f);

#ifdef _DEBUG
    auto hud = new HUD();
    hud->add(new FPSCounter(60));
    getEngine().setHUD(hud);
#endif
}
