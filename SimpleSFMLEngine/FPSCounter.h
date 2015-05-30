#pragma once
#include "Node.h"

class FPSCounter :
    public Node
{
public:
    FPSCounter(int frameRateLimit, std::string fontName = "04B_03__");
    
    virtual void init() override;
    virtual void update() override;
    virtual void render(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::FloatRect getLocalBounds();
    sf::FloatRect getGlobalBounds();

private:
    sf::Font font;
    sf::Text fpsCounter;

};

