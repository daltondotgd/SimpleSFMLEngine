#include "stdafx.h"
#include "Shake.h"

Shake::Shake(float duration, float strength)
    : duration(duration), strength(strength)
{
}

void Shake::update()
{
    getParent().move(-lastOffset);

    duration -= getEngine().deltaTime();
    if (duration < 0.f)
        getParent().remove(this);
    else
    {
        lastOffset = Vector2((rand() / (float)RAND_MAX) * 2 * strength - strength, (rand() / (float)RAND_MAX) * 2 * strength - strength);
        getParent().move(lastOffset);
    }
}
