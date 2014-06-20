#ifndef PHYSICS_COLLISIONCOMPONENT_H
#define PHYSICS_COLLISIONCOMPONENT_H

#include "../Ecs/Component.h"
#include "CollisionBody.h"

namespace Physics
{
    class CollisionComponent : public Ecs::Component
    {
    public:
        static const Ecs::Component::Type Type;

        CollisionComponent(const CollisionBody& collisionBody):
            Ecs::Component(Type),
            collisionBody_(collisionBody)
        {}

        virtual Component* clone() const
        {
            return new CollisionComponent(collisionBody_);
        }

        virtual const std::vector<Ecs::Component::Type>& getDependentComponents();

        const CollisionBody& getCollisionBody() const
        {
            return collisionBody_;
        }

    private:
        static std::vector<Ecs::Component::Type> dependentTypes_;
        CollisionBody collisionBody_;
    };
}

#endif // PHYSICS_COLLISIONCOMPONENT_H
