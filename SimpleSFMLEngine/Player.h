#pragma once
#include "AnimatedSprite.h"

class Player :
    public AnimatedSprite
{
public:
    Player();

    virtual void init() override;
    virtual void update() override;
private:
    Sprite* testRect;

};

