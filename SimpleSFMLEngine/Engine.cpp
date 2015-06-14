#include "stdafx.h"
#include "Engine.h"

#include "World.h"
#include "HUD.h"

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

sf::View& Engine::getCamera()
{
    return camera;
}

void Engine::setWorld(World* newWorld)
{
    world = newWorld;
    world->engine = this;
    world->parent = nullptr;
    world->activate();
}

void Engine::setHUD(HUD * newHUD)
{
    hud = newHUD;
    hud->engine = this;
    hud->parent = nullptr;
    hud->activate();
}

void Engine::init(const sf::VideoMode& videoMode, const std::string& title, int frameRateLimit, World* world, sf::Uint32 style, const sf::ContextSettings& settings, bool vsync)
{
    window = new sf::RenderWindow(videoMode, title, style, settings);
    window->setVerticalSyncEnabled(vsync);
    window->setFramerateLimit(frameRateLimit);

    camera.setCenter(videoMode.width / 2, videoMode.height / 2);
    camera.setSize(videoMode.width, videoMode.height);

    setWorld(world);

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

std::string text = "";

void Engine::handleEvents()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();

        if (event.type == sf::Event::LostFocus)
        {
            suspended = true;
        }

        if (event.type == sf::Event::GainedFocus)
        {
            suspended = false;
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            exit(0);

        world->passEvent(event);
    }
}

void Engine::mainLoop()
{
    clock.restart();
    render();
    update();
    world->performRemove();
    dt = clock.getElapsedTime().asSeconds();
    time += dt;
}

void Engine::update()
{
    world->updateNode();
    hud->updateNode();
}

void Engine::render()
{
    window->setView(camera);

    window->clear();
    sf::RenderStates states;
    world->draw(*window, states);

    if (hud)
    {
        window->setView(window->getDefaultView());
        hud->draw(*window, states);
    }

    window->display();
}
