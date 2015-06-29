#pragma once
#include "Node.h"

typedef std::uint64_t BitMask;

class PhysicalNode :
    public Node
{
public:
    PhysicalNode();
    virtual ~PhysicalNode();

    virtual sf::Shape* getCollisionShape() const;
    virtual void setCollisionShape(sf::Shape* shape);

    virtual void beforeRemoved();
    virtual class PhysicalWorld* getPhysicalWorld();
    virtual void setPhysicalWorld(class PhysicalWorld* world);

    BitMask getMask();
    void setMask(BitMask mask);

protected:
    virtual void updateNode() override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Shape* collisionShape{ nullptr };
    class PhysicalWorld* physicalWorld;

    BitMask bitmask{ 1 };

};