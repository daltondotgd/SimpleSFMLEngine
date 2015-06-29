#pragma once

#include "Node.h"
#include "PhysicalNode.h"

class PhysicalWorld :
    public Node
{
public:
    PhysicalWorld();
    virtual ~PhysicalWorld();

    virtual void update() override;

    virtual void onCollisionBegin(PhysicalNode* nodeA, PhysicalNode* nodeB) const;
    virtual void onCollision(PhysicalNode* nodeA, PhysicalNode* nodeB) const;
    virtual void onCollisionEnd(PhysicalNode* nodeA, PhysicalNode* nodeB) const;
    bool collides(PhysicalNode* nodeA, PhysicalNode* nodeB) const;

    virtual void add(PhysicalNode* node);
    virtual void remove(PhysicalNode* node);

    virtual std::vector<PhysicalNode*>::iterator findWithMask(uint8_t mask);

private:
    struct Bounds1D {
        float min;
        float max;
    };
    Bounds1D getBoundsAlongAxis(PhysicalNode* node, const Vector2& axis) const;

    std::vector<PhysicalNode*> physicalNodes;

};

