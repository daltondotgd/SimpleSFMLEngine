#pragma once
class ShaderManager
{
public:
    ShaderManager();
    ~ShaderManager();

    void preloadShader(const std::string& path);
    sf::Shader* getShader(const std::string& path);
    sf::Shader * operator[](const std::string & path);
    void unloadShader(const std::string& path);

    void setShadersPath(std::string dir);

private:
    std::map<std::string, sf::Shader*> shaders;
    std::string shadersPath;
};

