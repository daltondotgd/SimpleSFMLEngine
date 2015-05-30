#pragma once

#include "Node.h"

class Sprite :
    public Node
{
public:
    Sprite() : texture(nullptr) {}
    Sprite(const std::string& texturePath, const sf::Vector2f& position = sf::Vector2f());

    void setTexture(sf::Texture* texture, bool resetRect = false);
    void setTextureRect(const sf::IntRect& rectangle);
    void setColor(const sf::Color& color);
    const sf::Texture* getTexture() const;
    const sf::IntRect& getTextureRect() const;
    const sf::Color& getColor() const;
    sf::FloatRect getLocalBounds() const;
    sf::FloatRect getGlobalBounds() const;

protected:
    virtual void render(sf::RenderTarget& target, sf::RenderStates states) const override;
    void updatePositions();
    void updateTexCoords();

    sf::Vertex vertices[4];
    sf::Texture* texture;
    sf::IntRect textureRect;

};