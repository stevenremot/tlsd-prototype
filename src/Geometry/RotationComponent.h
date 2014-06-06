#ifndef GEOMETRY_ROTATIONCOMPONENT_H
#define GEOMETRY_ROTATIONCOMPONENT_H


#include "../Ecs/Component.h"
#include "Vec3D.h"

namespace Geometry
{
    /**
     * Component which add a rotation (in degrees) to an entity
     */
    class RotationComponent : public Ecs::Component
    {
    public:
        static const Ecs::Component::Type Type;

        static const std::vector<Ecs::Component::Type> Dependencies;

        RotationComponent(const Vec3Df & rotation): Component(Type),
            rotation_(rotation)
            {}

        virtual const std::vector<Ecs::Component::Type>& getDependentComponents()
        {
            return Dependencies;
        }

        const Vec3Df & getRotation() const
        {
            return rotation_;
        }

        void setRotation(const Vec3Df & rotation)
        {
            rotation_ = rotation;
        }

    private:
        Vec3Df rotation_;
    };
}

#endif // GEOMETRY_ROTATIONCOMPONENT_H
