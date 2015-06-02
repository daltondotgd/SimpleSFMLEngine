#include "stdafx.h"
#include "Player.h"

#include "Engine.h"

Player::Player()
    : AnimatedSprite("player2")
{
}

void Player::init()
{
    auto view = Engine::getInstance().getWindow()->getView();
    auto viewport = Engine::getInstance().getWindow()->getViewport(view);
    setPosition(viewport.width / 2.f, viewport.height / 2.f);
    testRect = new Sprite("sample-sprite");
    testRect->setPosition(20, 20);
    add(testRect);

    setShader("test");
    shader->setParameter("texture", sf::Shader::CurrentTexture);

    registerFrameCallback("idle", 6, []() { LOG("Should show up when 6th frame of idle is shown."); });
}

void Player::update()
{
    shader->setParameter("time", Engine::getInstance().globalTime());

    Vector2 direction;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) direction.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) direction.x += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) direction.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) direction.y += 1;
    move(direction);
    //move(cos(Engine::getInstance().globalTime() / 2.f), cos(Engine::getInstance().globalTime()));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) getParent()->remove(testRect);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) toggleAnimation();
}