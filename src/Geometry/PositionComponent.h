#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include "../Ecs/Component.h"
#include "Vec3D.h"

namespace Geometry
{
    /**
     * Component which add a position to an entity
     */
    class PositionComponent : public Ecs::Component
    {
    public:
        static const Ecs::Component::Type Type;

        static const std::vector<Ecs::Component::Type> Dependencies;

        PositionComponent(const Vec3Df & position): Component(Type),
            position_(position)
        {}

        virtual Component* clone() const
        {
            return new PositionComponent(position_);
        }

        virtual const std::vector<Ecs::Component::Type>& getDependentComponents()
        {
            return Dependencies;
        }

        const Vec3Df & getPosition() const
        {
            return position_;
        }

        void setPosition(const Vec3Df & position)
        {
            position_ = position;
        }

    private:
        Vec3Df position_;
    };
}
#endif // POSITIONCOMPONENT_H
