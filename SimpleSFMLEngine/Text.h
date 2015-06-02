#pragma once
#include "Node.h"
class Text :
    public Node
{
public:
    Text(std::string txt, std::string fontName = "04B_03__");

    virtual void render(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setString(const std::string& string);
    const std::string& getString() const;

    void setFont(const sf::Font& font);
    const sf::Font* getFont() const;

    void setCharacterSize(unsigned int size);
    unsigned int getCharacterSize() const;

    void setStyle(sf::Uint32 style);
    sf::Uint32 getStyle() const;

    void setColor(const sf::Color& color);
    const sf::Color& getColor() const;

    sf::Vector2f findCharacterPos(std::size_t index) const;
    sf::FloatRect getLocalBounds() const;
    sf::FloatRect getGlobalBounds() const;

private:
    sf::Font font;
    sf::Text text;

};

