#include "stdafx.h"
#include "SATWorld.h"

#include "HUD.h"
#include "FPSCounter.h"
#include "Text.h"
#include "PhysicalNode.h"

SATWorld::SATWorld()
{
}


SATWorld::~SATWorld()
{
    delete [] verts;
}

void SATWorld::init()
{
    rectA = sf::CircleShape(50);
    rectA.setFillColor(sf::Color(128, 255, 128, 64));
    rectA.setOutlineColor(sf::Color(128, 255, 128, 255));
    rectA.setOutlineThickness(1);
    rectA.setOrigin(50, 50);
    rectA.setPosition(500, 200);
    rectA.rotate(45);

    rectB = sf::RectangleShape(Vector2(200, 100));
    rectB.setFillColor(sf::Color(128, 128, 255, 64));
    rectB.setOutlineColor(sf::Color(128, 128, 255, 255));
    rectB.setOutlineThickness(1);
    rectB.setOrigin(100, 50);
    rectB.setPosition(200, 300);
    rectB.rotate(15);

    auto physnode = new PhysicalNode();
    physnode->setCollisionShape(new sf::RectangleShape(Vector2(100, 100)));
    physnode->setPosition(100, 100);
    add(physnode);

    auto hud = new HUD();
    getEngine().setHUD(hud);

    collisionInfoText = new Text("collides: false");
    collisionInfoText->setCharacterSize(16);
    collisionInfoText->setPosition(4, getEngine().getWindow()->getSize().y - 2 * collisionInfoText->getCharacterSize() - 8);
    hud->add(collisionInfoText);

    mouseInfoText = new Text("mouse: (000, 000)");
    mouseInfoText->setCharacterSize(16);
    mouseInfoText->setPosition(4, getEngine().getWindow()->getSize().y - mouseInfoText->getCharacterSize() - 4);
    hud->add(mouseInfoText);

//#ifdef _DEBUG
    hud->add(new FPSCounter(60));
//#endif

    // SETUP GRID
    int divSize = 10;
    int xdivs = getEngine().getWindow()->getSize().x / divSize;
    int ydivs = getEngine().getWindow()->getSize().y / divSize;
    vertsCount = 2 * xdivs + 2 * ydivs;

    int wWidth = getEngine().getWindow()->getSize().x;
    int wHeight = getEngine().getWindow()->getSize().y;
    verts = new sf::Vertex[vertsCount];
    sf::Color gridColor(255, 255, 255, 16);
    for (int x = 0; x < 2 * xdivs; x += 2)
    {
        verts[x] = sf::Vertex(Vector2((x / 2) * divSize, 0), gridColor);
        verts[x + 1] = sf::Vertex(Vector2((x / 2) * divSize, wHeight), gridColor);
    }
    for (int y = 2 * xdivs; y < vertsCount; y += 2)
    {
        verts[y] = sf::Vertex(Vector2(0, ((y - 2 * xdivs) / 2) * divSize), gridColor);
        verts[y + 1] = sf::Vertex(Vector2(wWidth, ((y - 2 * xdivs) / 2) * divSize), gridColor);
    }

    getEngine().getWindow()->setMouseCursorVisible(false);
}

void SATWorld::recieveEvent(const sf::Event & event)
{
    if (event.type == sf::Event::KeyPressed
        && event.key.code == sf::Keyboard::R) getEngine().getCamera().reset(sf::FloatRect(0, 0, getEngine().getWindow()->getDefaultView().getSize().x, getEngine().getWindow()->getDefaultView().getSize().y));

    if (event.type == sf::Event::MouseWheelMoved)
    {
        //getEngine().getCamera().zoom(event.mouseWheel.delta < 0 ? event.mouseWheel.delta * -1.25f : event.mouseWheel.delta * 0.75f);
        //getEngine().getCamera().setCenter(event.mouseWheel.x, event.mouseWheel.y);
        rectB.rotate(event.mouseWheel.delta);
    }

    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Button::Middle)
            mmbPressed = true;
    }
    if (event.type == sf::Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == sf::Mouse::Button::Middle)
            mmbPressed = false;
    }
    if (mmbPressed)
        getEngine().getCamera().setCenter(event.mouseMove.x, event.mouseMove.y);

    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Button::Right)
            rmbPressed = true;
    }
    if (event.type == sf::Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == sf::Mouse::Button::Right)
            rmbPressed = false;
    }
    auto pos = sf::Mouse::getPosition(*getEngine().getWindow());
    if (rmbPressed)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            rectA.setPosition(pos.x, pos.y);
        else
            rectB.setPosition(pos.x, pos.y);

    // OLD THINGS FROM UPDATE
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !lmbPressed)
    {
        lmbPressed = true;
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            start = Vector2(sf::Mouse::getPosition(*getEngine().getWindow()).x, sf::Mouse::getPosition(*getEngine().getWindow()).y);
        else
            start = Vector2(std::round(sf::Mouse::getPosition(*getEngine().getWindow()).x / 10.f) * 10, std::round(sf::Mouse::getPosition(*getEngine().getWindow()).y / 10.f) * 10);
    }
    else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        lmbPressed = false;
    }

    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        current = Vector2(sf::Mouse::getPosition(*getEngine().getWindow()).x, sf::Mouse::getPosition(*getEngine().getWindow()).y);
    else
        current = Vector2(std::round(sf::Mouse::getPosition(*getEngine().getWindow()).x / 10.f) * 10, std::round(sf::Mouse::getPosition(*getEngine().getWindow()).y / 10.f) * 10);
}

struct MinMax
{
    float min;
    float max;
};

MinMax getMinMax(const sf::Shape& shape, Vector2 axis)
{
    auto min = Vector2(shape.getTransform() * shape.getPoint(0)).dot(axis);
    auto max = min;

    for (int i = 1; i < shape.getPointCount(); ++i)
    {
        auto current = Vector2(shape.getTransform() * shape.getPoint(i)).dot(axis);
        if (min > current) min = current;
        if (current > max) max = current;
    }

    return { min, max };
}

struct ResultingPoint
{
    bool exists{ false };
    Vector2 point{ 0, 0 };
};

// http://www.ahristov.com/tutorial/geometry-games/intersection-segments.html
ResultingPoint intersection(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4)
{
    ResultingPoint result;

    auto d = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);
    if (d == 0) return result;

    Vector2 p;
    p.x = ((p3.x - p4.x) * (p1.x * p2.y - p1.y * p2.x) - (p1.x - p2.x) * (p3.x * p4.y - p3.y * p4.x)) / d;
    p.y = ((p3.y - p4.y) * (p1.x * p2.y - p1.y * p2.x) - (p1.y - p2.y) * (p3.x * p4.y - p3.y * p4.x)) / d;
    result.point = p;

    if (p.x < std::min(p1.x, p2.x) || p.x > std::max(p1.x, p2.x)) return result;
    if (p.x < std::min(p3.x, p4.x) || p.x > std::max(p3.x, p4.x)) return result;

    result.exists = true;
    return result;
}

std::vector<Vector2> intersections;

bool collides(const sf::Shape& A, const sf::Shape& B) //const
{
    intersections.clear();
    std::vector<Vector2> normalsA(A.getPointCount() / 2);
    std::vector<Vector2> normalsB(B.getPointCount() / 2);

    for (int n = 0; n < A.getPointCount(); ++n)
    {
        int i = n + 1;
        if (i >= A.getPointCount()) i = 0;

        auto vector = A.getTransform() * A.getPoint(i) - A.getTransform() * A.getPoint(n);
        auto normal = Vector2(vector.y, -vector.x);
        
        normalsA.push_back(normal);
    }

    for (int n = 0; n < B.getPointCount(); ++n)
    {
        int i = n + 1;
        if (i >= B.getPointCount()) i = 0;

        auto vector = B.getTransform() * B.getPoint(i) - B.getTransform() * B.getPoint(n);
        auto normal = Vector2(vector.y, -vector.x);

        normalsB.push_back(normal);
    }

    bool separated = true;
    for (auto normal : normalsA)
    {
        auto MMA = getMinMax(A, normal);
        auto MMB = getMinMax(B, normal);

        separated = MMA.max < MMB.min || MMB.max < MMA.min;
        if (separated) break;
    }
    if (!separated)
    {
        for (auto normal : normalsB)
        {
            auto MMA = getMinMax(A, normal);
            auto MMB = getMinMax(B, normal);

            separated = MMA.max < MMB.min || MMB.max < MMA.min;
            if (separated) break;
        }
    }

    if (!separated)
    {
        int count = 0;
        for (int n = 0; n < A.getPointCount(); ++n)
        {
            int i = n + 1;
            if (i >= A.getPointCount()) i = 0;

            for (int k = 0; k < B.getPointCount(); ++k)
            {
                int j = k + 1;
                if (j >= B.getPointCount()) j = 0;

                auto p1 = A.getTransform() * A.getPoint(n);
                auto p2 = A.getTransform() * A.getPoint(i);
                auto p3 = B.getTransform() * B.getPoint(k);
                auto p4 = B.getTransform() * B.getPoint(j);

                auto p = intersection(p1, p2, p3, p4);
                if (p.exists)
                {
                    intersections.push_back(p.point);
                    break;
                }
                count++;
            }
        }
        LOGV(count);
    }

    return !separated;
}

void SATWorld::update()
{
    if (collides(rectA, rectB))
        collisionInfoText->setString("collides: true");
    else
        collisionInfoText->setString("collides: false");
}

void SATWorld::render(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(verts, vertsCount, sf::Lines);
    target.draw(rectA, states);
    target.draw(rectB, states);

    if (lmbPressed)
    {
        sf::CircleShape s(2.5);
        s.setOrigin(2.5, 2.5);
        s.setPosition(start);
        target.draw(s);

        sf::Vertex mouse[] = { sf::Vertex(start), sf::Vertex(current) };
        target.draw(mouse, 2, sf::Lines);
    }

    {
        auto hor = Vector2(0, 10);
        auto vert = Vector2(10, 0);
        sf::Vertex cursor[] = { sf::Vertex(current - hor), sf::Vertex(current + hor),
                                sf::Vertex(current - vert), sf::Vertex(current + vert) };
        target.draw(cursor, 4, sf::Lines);

        auto mouseStr = "mouse: (" + std::to_string((int)current.x) + ", " + std::to_string((int)current.y) + ")";
        if (lmbPressed) mouseStr += ", length: " + std::to_string((current - start).mag());
        mouseInfoText->setString(mouseStr);
    }

    for (auto p : intersections)
    {
        auto hor = Vector2(0, 10);
        auto vert = Vector2(10, 0);
        sf::Vertex x[] = { sf::Vertex(p - hor, sf::Color::Cyan), sf::Vertex(p + hor, sf::Color::Cyan),
            sf::Vertex(p - vert, sf::Color::Cyan), sf::Vertex(p + vert, sf::Color::Cyan) };
        target.draw(x, 4, sf::Lines);

        sf::CircleShape s(10);
        s.setFillColor(sf::Color::Transparent);
        s.setOutlineColor(sf::Color::Cyan);
        s.setOutlineThickness(1);
        s.setOrigin(10, 10);
        s.setPosition(p);
        target.draw(s);
    }
}