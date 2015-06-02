#pragma once

#include "Engine.h"

class Node
    : public sf::Drawable, public sf::Transformable
{
public:
    Node();
    ~Node();

    virtual void init();
    virtual void update();

    virtual void add(Node* child);
    virtual void remove(Node* child);
    virtual void performRemove();
    virtual void clearChildren();

    virtual void render(sf::RenderTarget & target, sf::RenderStates states) const;

    Node* getParent() const;
    std::vector<Node*> getChildren() const;

    void setShader(sf::Shader* shaderProgram);
    void setShader(std::string shaderName);
    sf::Shader* getShader() const;
    void removeShader();

    void setBlendMode(sf::BlendMode mode);
    sf::BlendMode getBlendMode() const;

    Engine& getEngine() const;

    Vector2& getPosition() const;
    Vector2& getScale() const;
    Vector2& getOrigin() const;

protected:
    virtual void activate();
    virtual void updateNode();
    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
    friend Engine;

    Engine* engine{ nullptr };
    Node* parent{ nullptr };

    sf::Shader* shader{ nullptr };
    sf::BlendMode blendMode{ sf::BlendNone };

    std::vector<Node*> children;
    bool toBeRemoved{ false };

    bool active{ false };
};

