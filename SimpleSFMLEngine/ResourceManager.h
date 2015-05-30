#pragma once

#include "helpers.h"

template <class T>
class ResourceManager
{
public:
    ResourceManager()
    {
        setDefaultPath("Resources/");
        setResourceExtension("");
    }

    ~ResourceManager()
    {
        for (auto& resource = resources.rbegin(); resource != resources.rend(); ++resource)
        {
            delete resource->second;
            resource->second = nullptr;
        }

        resources.clear();
    }

    void preloadResource(const std::string& path)
    {
        if (resources.find(path) == resources.end())
        {
            auto resource = new T();
            if (resource->loadFromFile(resourcesPath + path + resourceExtension))
                resources[path] = resource;
        }
    }

    T* getResource(const std::string& path)
    {
        preloadResource(path);
        return resources[path];
    }

    T* operator[](const std::string& path)
    {
        preloadResource(path);
        return resources[path];
    }

    void unloadResource(const std::string& path)
    {
        delete resources[path];
        resources[path] = nullptr;
        resources.erase(path);
    }


    void setDefaultPath(std::string dir)
    {
        if (!endsWith(dir, "/")) dir += "/";
        resourcesPath = dir;
    }

    void setResourceExtension(std::string ext)
    {
        if (!startsWith(ext, ".")) ext = "." + ext;
        resourceExtension = ext;
    }

private:
    std::map<std::string, T*> resources;
    std::string resourcesPath;
    std::string resourceExtension;

};
