#pragma once

#include "ResourceManager.h"
#include "ShaderManager.h"

class Engine
{
public:
    static Engine& getInstance();

    void init(const sf::VideoMode& videoMode, const std::string& title, int frameRateLimit, class World* world, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());
    class World* getWorld();
    sf::RenderWindow* getWindow();
    sf::Clock getClock();

    float deltaTime() { return dt; }
    float globalTime() { return time; }

    ResourceManager<sf::Font>& getFontManager();
    ResourceManager<sf::Texture>& getTextureManager();
    ResourceManager<sf::Sound>& getSoundManager();
    ResourceManager<sf::Music>& getMusicManager();
    ShaderManager& getShaderManager();

private:
    void createWindow(const sf::VideoMode& videoMode, const std::string& title, int frameRateLimit = 60, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());
    void run();

    void handleEvents();
    void mainLoop();

    void update();
    void render();

    ResourceManager<sf::Texture> textureManager;
    ResourceManager<sf::Font> fontManager;
    ResourceManager<sf::Sound> soundManager;
    ResourceManager<sf::Music> musicManager;
    ShaderManager shaderManager;

    class World* world;
    sf::RenderWindow* window;
    sf::Clock clock;

    bool suspended{ false };

    float dt;
    float time;

    Engine();
    ~Engine();
};

