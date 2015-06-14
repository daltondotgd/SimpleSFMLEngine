#pragma 
#include "World.h"

class SATWorld :
    public World
{
public:
    SATWorld();
    ~SATWorld();

    virtual void init() override;
    virtual void update() override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void recieveEvent(const sf::Event& event) override;

private:
    sf::CircleShape rectA;
    sf::RectangleShape rectB;

    bool lmbPressed = false;
    bool mmbPressed = false;
    bool rmbPressed = false;
    Vector2 start;
    Vector2 current;

    sf::Vertex* verts;
    int vertsCount = 0;

    class Text* collisionInfoText;
    class Text* mouseInfoText;
};

