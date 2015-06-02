#include "stdafx.h"
#include "Sprite.h"

#include "Engine.h"
#include "GameWorld.h"

#if defined(WIN32) && !defined(_DEBUG)
#define _WIN32_WINNT 0x0500 
#include <windows.h>
#endif

int main()
{
#if defined(WIN32) && !defined(_DEBUG)
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);
#endif

    auto gameWorld = new GameWorld();
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 8;

#ifdef _DEBUG
    Engine::getInstance().init(sf::VideoMode(800, 600), "Best game evar!", 60, gameWorld, sf::Style::Default, settings);
#else
    Engine::getInstance().init(sf::VideoMode::getDesktopMode(), "Best game evar!", 60, gameWorld, sf::Style::None, settings);
#endif

    return 0;
}