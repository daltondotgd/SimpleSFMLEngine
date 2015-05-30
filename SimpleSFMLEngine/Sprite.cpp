#include "stdafx.h"
#include "Sprite.h"

#include "Engine.h"

Sprite::Sprite(const std::string& texturePath, const sf::Vector2f& position)
{
    if (texturePath != "")
        setTexture(Engine::getInstance().getTextureManager()[texturePath]);

    setPosition(position);
}


void Sprite::setTexture(sf::Texture* tex, bool resetRect)
{
    if (resetRect || (!tex && (textureRect == sf::IntRect())) || (textureRect.width == 0 && textureRect.height == 0))
        setTextureRect(sf::IntRect(0, 0, tex->getSize().x, tex->getSize().y));

    texture = tex;
}

void Sprite::setTextureRect(const sf::IntRect & rectangle)
{
    if (rectangle != textureRect)
    {
        textureRect = rectangle;
        updatePositions();
        updateTexCoords();

        setOrigin(textureRect.width / 2.f, textureRect.height / 2.f);
    }
}

void Sprite::setColor(const sf::Color & color)
{
    vertices[0].color = color;
    vertices[1].color = color;
    vertices[2].color = color;
    vertices[3].color = color;
}

const sf::Texture * Sprite::getTexture() const
{
    return texture;
}

const sf::IntRect & Sprite::getTextureRect() const
{
    return textureRect;
}

const sf::Color & Sprite::getColor() const
{
    return vertices[0].color;
}

sf::FloatRect Sprite::getLocalBounds() const
{
    float width = static_cast<float>(std::abs(textureRect.width));
    float height = static_cast<float>(std::abs(textureRect.height));

    return sf::FloatRect(0.f, 0.f, width, height);
}

sf::FloatRect Sprite::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}

void Sprite::render(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (texture)
    {
        states.texture = texture;
        target.draw(vertices, 4, sf::TrianglesStrip, states);
    }
}

void Sprite::updatePositions()
{
    sf::FloatRect bounds = getLocalBounds();

    vertices[0].position = sf::Vector2f(0, 0);
    vertices[1].position = sf::Vector2f(0, bounds.height);
    vertices[2].position = sf::Vector2f(bounds.width, 0);
    vertices[3].position = sf::Vector2f(bounds.width, bounds.height);
}

void Sprite::updateTexCoords()
{
    float left = static_cast<float>(textureRect.left);
    float right = left + textureRect.width;
    float top = static_cast<float>(textureRect.top);
    float bottom = top + textureRect.height;

    vertices[0].texCoords = sf::Vector2f(left, top);
    vertices[1].texCoords = sf::Vector2f(left, bottom);
    vertices[2].texCoords = sf::Vector2f(right, top);
    vertices[3].texCoords = sf::Vector2f(right, bottom);
}
