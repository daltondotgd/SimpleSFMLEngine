#pragma once
#include "World.h"
class GameWorld :
    public World
{
public:
    GameWorld();
    ~GameWorld();

    virtual void init() override;

private:
    class Player* player;

};

