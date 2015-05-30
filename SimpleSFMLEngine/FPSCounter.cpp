#include "stdafx.h"
#include "FPSCounter.h"

#include "Engine.h"

FPSCounter::FPSCounter(int frameRateLimit, std::string fontName)
{
    font = *Engine::getInstance().getFontManager()[fontName];
    fpsCounter.setFont(font);

    auto fpsString = "FPS: " + (frameRateLimit ? std::to_string(frameRateLimit) : std::to_string(9999));

    fpsCounter.setString(fpsString);
    fpsCounter.setCharacterSize(16);
    fpsCounter.setColor(sf::Color::White);
}

void FPSCounter::init()
{
    setPosition(Engine::getInstance().getWindow()->getSize().x - (fpsCounter.getLocalBounds().width + 10), Engine::getInstance().getWindow()->getSize().y - (fpsCounter.getLocalBounds().height + 15));
}

void FPSCounter::update()
{
    int fps = std::round(1.f / Engine::getInstance().deltaTime());
    fpsCounter.setString("FPS: " + std::to_string(fps));
}

void FPSCounter::render(sf::RenderTarget & target, sf::RenderStates states) const
{
    target.draw(fpsCounter, states);
}

sf::FloatRect FPSCounter::getLocalBounds()
{
    return fpsCounter.getLocalBounds();
}

sf::FloatRect FPSCounter::getGlobalBounds()
{
    return fpsCounter.getGlobalBounds();
}
