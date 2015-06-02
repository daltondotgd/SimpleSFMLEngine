#include "stdafx.h"
#include "Text.h"

#include "Engine.h"

Text::Text(std::string text, std::string fontName)
{
    font = *Engine::getInstance().getFontManager()[fontName];

    setFont(font);
    setString(text);
}

void Text::render(sf::RenderTarget & target, sf::RenderStates states) const
{
    target.draw(text, states);
}

void Text::setString(const std::string & string)
{
    text.setString(string);
}

const std::string & Text::getString() const
{
    return text.getString();
}

void Text::setFont(const sf::Font & newFont)
{
    font = newFont;
    text.setFont(newFont);
}

const sf::Font * Text::getFont() const
{
    return text.getFont();
}

void Text::setCharacterSize(unsigned int size)
{
    text.setCharacterSize(size);
}

unsigned int Text::getCharacterSize() const
{
    return text.getCharacterSize();
}

void Text::setStyle(sf::Uint32 style)
{
    text.setStyle(style);
}

sf::Uint32 Text::getStyle() const
{
    return text.getStyle();
}

void Text::setColor(const sf::Color & color)
{
    text.setColor(color);
}

const sf::Color & Text::getColor() const
{
    return text.getColor();
}

sf::Vector2f Text::findCharacterPos(std::size_t index) const
{
    return text.findCharacterPos(index);
}

sf::FloatRect Text::getLocalBounds() const
{
    return text.getLocalBounds();
}

sf::FloatRect Text::getGlobalBounds() const
{
    return text.getGlobalBounds();
}
