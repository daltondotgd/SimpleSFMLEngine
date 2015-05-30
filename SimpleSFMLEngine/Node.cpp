#include "stdafx.h"
#include "Node.h"

#include "Engine.h"

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

void Node::add(Node * child)
{
    child->parent = this;
    child->init();
    children.push_back(child);
}

void Node::remove(Node * child)
{
    child->toBeRemoved = true;
}

void Node::performRemove()
{
    for (auto child = children.begin(); child != children.end();)
    {
        if ((*child)->toBeRemoved)
        {
            (*child)->clearChildren();
            delete (*child);
            (*child) = nullptr;
            child = children.erase(child);
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

void Node::render(sf::RenderTarget & target, sf::RenderStates states) const
{
}

Node* Node::getParent() const
{
    return parent;
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

sf::Shader * Node::getShader()
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

sf::BlendMode Node::getBlendMode()
{
    return blendMode;
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
