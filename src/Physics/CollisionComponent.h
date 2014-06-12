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

        CollisionComponent(CollisionBody collisionBody):
            Ecs::Component(Type),
            collisionBody_(collisionBody)
            {}

        virtual const std::vector<Ecs::Component::Type>& getDependentComponents();

    private:
        static std::vector<Ecs::Component::Type> dependentTypes_;
        CollisionBody collisionBody_;
    };
}

#endif // PHYSICS_COLLISIONCOMPONENT_H
