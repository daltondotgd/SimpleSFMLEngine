#include "stdafx.h"
#include "FPSCounter.h"

#include "Engine.h"

FPSCounter::FPSCounter(int frameRateLimit, std::string fontName)
    : Text("FPS: " + (frameRateLimit ? std::to_string(frameRateLimit) : std::to_string(9999)), fontName)
{
    setCharacterSize(16);
    setColor(sf::Color::White);
}

void FPSCounter::init()
{
    setPosition(getEngine().getWindow()->getSize().x - (getLocalBounds().width + 10), getEngine().getWindow()->getSize().y - (getLocalBounds().height + 15));
}

void FPSCounter::update()
{
    int fps = std::round(1.f / Engine::getInstance().deltaTime());
    setString("FPS: " + std::to_string(fps));
}
