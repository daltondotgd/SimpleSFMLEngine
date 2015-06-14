#pragma once
#include "Action.h"
class Shake :
    public Action
{
public:
    Shake(float duration = .2f, float strength = .5f);

    virtual void update() override;

private:
    float duration;
    float strength;

    Vector2 lastOffset;

};

