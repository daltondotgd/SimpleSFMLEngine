#include "stdafx.h"
#include "PhysicalNode.h"
#include "PhysicalWorld.h"


PhysicalNode::PhysicalNode()
{
}


PhysicalNode::~PhysicalNode()
{
    if (collisionShape) delete collisionShape;
}

sf::Shape * PhysicalNode::getCollisionShape() const
{
    return collisionShape;
}

void PhysicalNode::setCollisionShape(sf::Shape * shape)
{
#if _DEBUG
    std::uint8_t r = rand() % 256;
    std::uint8_t g = rand() % 256;
    std::uint8_t b = rand() % 256;
    shape->setFillColor(sf::Color(r, g, b, 64));
    shape->setOutlineColor(sf::Color(r, g, b, 255));
    shape->setOutlineThickness(1);
#endif

    shape->setOrigin(shape->getLocalBounds().width / 2, shape->getLocalBounds().height / 2);
    collisionShape = shape;
}

void PhysicalNode::beforeRemoved()
{
    physicalWorld->remove(this);
}

PhysicalWorld * PhysicalNode::getPhysicalWorld()
{
    return physicalWorld;
}

void PhysicalNode::setPhysicalWorld(PhysicalWorld * world)
{
    physicalWorld = world;
}

BitMask PhysicalNode::getMask()
{
    return bitmask;
}

void PhysicalNode::setMask(BitMask mask)
{
    bitmask = mask;
}

void PhysicalNode::updateNode()
{
    Node::updateNode();

    if (collisionShape)
    {
        collisionShape->setPosition(getPosition());
        collisionShape->setRotation(getRotation());
        collisionShape->setScale(getScale());
    }
}

void PhysicalNode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    Node::draw(target, states);

#ifdef _DEBUG
    if (collisionShape)
        target.draw(*collisionShape, states);
#endif
}
