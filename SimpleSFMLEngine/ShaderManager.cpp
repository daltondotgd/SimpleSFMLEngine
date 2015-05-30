#include "stdafx.h"
#include "ShaderManager.h"

#include "helpers.h"

ShaderManager::ShaderManager()
{
    setShadersPath("Resources/shaders/");
}


ShaderManager::~ShaderManager()
{
    for (auto& shader = shaders.rbegin(); shader != shaders.rend(); ++shader)
    {
        delete shader->second;
        shader->second = nullptr;
    }

    shaders.clear();
}

void ShaderManager::preloadShader(const std::string & path)
{
    if (shaders.find(path) == shaders.end())
    {
        auto shader = new sf::Shader();
        if (shader->loadFromFile(shadersPath + path + ".vsh", sf::Shader::Vertex)
            && shader->loadFromFile(shadersPath + path + ".fsh", sf::Shader::Fragment))
            shaders[path] = shader;
    }
}

sf::Shader* ShaderManager::getShader(const std::string & path)
{
    preloadShader(path);
    return shaders[path];
}

sf::Shader* ShaderManager::operator[](const std::string & path)
{
    preloadShader(path);
    return shaders[path];
}

void ShaderManager::unloadShader(const std::string & path)
{
    delete shaders[path];
    shaders[path] = nullptr;
    shaders.erase(path);
}

void ShaderManager::setShadersPath(std::string dir)
{
    if (!endsWith(dir, "/")) dir += "/";
    shadersPath = dir;
}
