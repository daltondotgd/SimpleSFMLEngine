#pragma once

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
    sf::Shader* getShader();
    void removeShader();

    void setBlendMode(sf::BlendMode mode);
    sf::BlendMode getBlendMode();

protected:
    virtual void updateNode();
    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
    friend class Engine;

    Node* parent{ nullptr };
    sf::Shader* shader{ nullptr };
    sf::BlendMode blendMode{ sf::BlendNone };

    std::vector<Node*> children;
    bool toBeRemoved{ false };

};

