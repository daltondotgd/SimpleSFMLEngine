#include "stdafx.h"
#include "Engine.h"

#include "World.h"

Engine::Engine()
{
    textureManager.setDefaultPath("Resources/gfx/");
    textureManager.setResourceExtension(".png");

    fontManager.setDefaultPath("Resources/fonts/");
    fontManager.setResourceExtension(".ttf");

    soundManager.setDefaultPath("Resources/sfx/");
    soundManager.setResourceExtension(".wav");

    musicManager.setDefaultPath("Resources/mfx/");
    musicManager.setResourceExtension(".wav");

    shaderManager.setShadersPath("Resources/shaders/");
}


Engine::~Engine()
{
    delete world;
    world = nullptr;

    delete window;
    window = nullptr;
}

Engine & Engine::getInstance()
{
    static Engine instance;
    return instance;
}

void Engine::run()
{
    while (window->isOpen())
    {
        handleEvents();

        if (!suspended)
            mainLoop();
    }
}

ResourceManager<sf::Font>& Engine::getFontManager()
{
    return fontManager;
}

ResourceManager<sf::Texture>& Engine::getTextureManager()
{
    return textureManager;
}

ResourceManager<sf::Sound>& Engine::getSoundManager()
{
    return soundManager;
}

ResourceManager<sf::Music>& Engine::getMusicManager()
{
    return musicManager;
}

ShaderManager& Engine::getShaderManager()
{
    return shaderManager;
}

void Engine::createWindow(const sf::VideoMode& videoMode, const std::string& title, int frameRateLimit, sf::Uint32 style, const sf::ContextSettings& settings)
{
    window = new sf::RenderWindow(videoMode, title, style, settings);
    window->setFramerateLimit(frameRateLimit);
}

void Engine::init(const sf::VideoMode& videoMode, const std::string& title, int frameRateLimit, World* wrld, sf::Uint32 style, const sf::ContextSettings& settings)
{
    world = wrld;
    createWindow(videoMode, title, frameRateLimit, style, settings);

    world->initNode();
    run();
}

World * Engine::getWorld()
{
    return world;
}

sf::RenderWindow * Engine::getWindow()
{
    return window;
}

sf::Clock Engine::getClock()
{
    return clock;
}

void Engine::handleEvents()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();

        if (event.type == sf::Event::LostFocus)
            suspended = true;

        if (event.type == sf::Event::GainedFocus)
            suspended = false;

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            exit(0);
    }
}

void Engine::mainLoop()
{
    clock.restart();
    update();
    render();
    world->performRemove();
    dt = clock.getElapsedTime().asSeconds();
    time += dt;
}

void Engine::update()
{
    world->updateNode();
}

void Engine::render()
{
    window->clear();

    sf::RenderStates states;
    world->draw(*window, states);

    window->display();
}
