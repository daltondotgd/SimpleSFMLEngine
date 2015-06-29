#include "stdafx.h"
#include "Node.h"

Node::Node()
{
}


Node::~Node()
{
    clearChildren();
}

void Node::init()
{
}

void Node::update()
{
}

void Node::recieveEvent(const sf::Event& event)
{
}

void Node::add(Node* child)
{
    child->parent = this;
    if (active)
    {
        child->engine = engine;
        child->active = true;
        child->init();
    }
    children.push_back(child);
}

void Node::remove(Node* child)
{
    child->toBeRemoved = true;
}

void Node::beforeRemoved()
{
}

void Node::performRemove()
{
    for (auto child = children.begin(); child != children.end();)
    {
        if ((*child)->toBeRemoved)
        {
            auto tmp = *child;
            child = children.erase(child);
            tmp->clearChildren();
            delete tmp;
            tmp = nullptr;
        }
        else
        {
            (*child)->performRemove();
            ++child;
        }
    }
}

void Node::clearChildren()
{
    for (int i = 0; i < children.size(); ++i)
    {
        children[i]->clearChildren();

        delete children[i];
        children[i] = nullptr;
    }

    children.clear();
}

void Node::render(sf::RenderTarget& target, sf::RenderStates states) const
{
}

Node& Node::getParent() const
{
    return *parent;
}

std::vector<Node*> Node::getChildren() const
{
    return children;
}

void Node::setShader(sf::Shader* shaderProgram)
{
    shader = shaderProgram;
}

void Node::setShader(std::string shaderName)
{
    shader = Engine::getInstance().getShaderManager()[shaderName];
}

sf::Shader * Node::getShader() const
{
    return shader;
}

void Node::removeShader()
{
    shader = nullptr;
}

void Node::setBlendMode(sf::BlendMode mode)
{
    blendMode = mode;
}

sf::BlendMode Node::getBlendMode() const
{
    return blendMode;
}

Engine& Node::getEngine() const
{
    return *engine;
}

Vector2 const Node::getPosition() const
{
    auto position = sf::Transformable::getPosition();
    return Vector2(position.x, position.y);
}

Vector2 const Node::getScale() const
{
    auto scale = sf::Transformable::getScale();
    return Vector2(scale.x, scale.y);
}

Vector2 const Node::getOrigin() const
{
    auto origin = sf::Transformable::getOrigin();
    return Vector2(origin.x, origin.y);
}

void Node::activate()
{
    if (!active)
    {
        active = true;
        init();
        for (auto child : children)
        {
            child->engine = engine;
            child->activate();
        }
    }
}

void Node::updateNode()
{
    update();

    for (auto& child : children)
    {
        child->updateNode();
    }
}

void Node::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    if (shader) states.shader = shader;
    if (blendMode != sf::BlendNone) states.blendMode = blendMode;

    render(target, states);

    for (auto& child : children)
    {
        child->draw(target, states);
    }
}

void Node::passEvent(const sf::Event& event)
{
    recieveEvent(event);

    for (auto& child : children)
    {
        child->recieveEvent(event);
    }
}