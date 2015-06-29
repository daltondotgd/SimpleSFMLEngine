#include "stdafx.h"
#include "PhysicalWorld.h"


PhysicalWorld::PhysicalWorld()
{
}

PhysicalWorld::~PhysicalWorld()
{
}

void PhysicalWorld::update()
{
}

void PhysicalWorld::onCollisionBegin(PhysicalNode * nodeA, PhysicalNode * nodeB) const
{
}

void PhysicalWorld::onCollision(PhysicalNode * nodeA, PhysicalNode * nodeB) const
{
}

void PhysicalWorld::onCollisionEnd(PhysicalNode * nodeA, PhysicalNode * nodeB) const
{
}

bool PhysicalWorld::collides(PhysicalNode * nodeA, PhysicalNode * nodeB) const
{
    auto A = nodeA->getCollisionShape();
    auto B = nodeB->getCollisionShape();

    std::vector<Vector2> normalsA(A->getPointCount() / 2);
    std::vector<Vector2> normalsB(B->getPointCount() / 2);

    for (int n = 0; n < A->getPointCount(); ++n)
    {
        int i = n + 1;
        if (i >= A->getPointCount()) i = 0;

        auto vector = A->getTransform() * A->getPoint(i) - A->getTransform() * A->getPoint(n);
        auto normal = Vector2(vector.y, -vector.x);

        normalsA.push_back(normal);
    }

    for (int n = 0; n < B->getPointCount(); ++n)
    {
        int i = n + 1;
        if (i >= B->getPointCount()) i = 0;

        auto vector = B->getTransform() * B->getPoint(i) - B->getTransform() * B->getPoint(n);
        auto normal = Vector2(vector.y, -vector.x);

        normalsB.push_back(normal);
    }

    bool separated = true;
    for (auto normal : normalsA)
    {
        auto boundsA = getBoundsAlongAxis(nodeA, normal);
        auto boundsB = getBoundsAlongAxis(nodeB, normal);

        separated = boundsA.max < boundsB.min || boundsB.max < boundsA.min;
        if (separated) break;
    }
    if (!separated)
    {
        for (auto normal : normalsB)
        {
            auto boundsA = getBoundsAlongAxis(nodeA, normal);
            auto boundsB = getBoundsAlongAxis(nodeB, normal);

            separated = boundsA.max < boundsB.min || boundsB.max < boundsA.min;
            if (separated) break;
        }
    }

    return !separated;
}

void PhysicalWorld::add(PhysicalNode * node)
{
    node->setPhysicalWorld(this);
    physicalNodes.push_back(node);
}

void PhysicalWorld::remove(PhysicalNode* node)
{
    physicalNodes.erase(std::remove(physicalNodes.begin(), physicalNodes.end(), node), physicalNodes.end());
}

std::vector<PhysicalNode*>::iterator PhysicalWorld::findWithMask(uint8_t mask)
{
    auto result = std::find_if(physicalNodes.begin(), physicalNodes.end(), [=](PhysicalNode* node) {
        return (mask & node->getMask()) == mask;
    });
    return result;
}

PhysicalWorld::Bounds1D PhysicalWorld::getBoundsAlongAxis(PhysicalNode * node, const Vector2& axis) const
{
    auto shape = node->getCollisionShape();
    auto min = Vector2(shape->getTransform() * shape->getPoint(0)).dot(axis);
    auto max = min;

    for (int i = 1; i < shape->getPointCount(); ++i)
    {
        auto current = Vector2(shape->getTransform() * shape->getPoint(i)).dot(axis);
        if (min > current) min = current;
        if (current > max) max = current;
    }

    return{ min, max };
}
