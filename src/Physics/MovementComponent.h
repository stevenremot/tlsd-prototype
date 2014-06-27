/*
   This file is part of The Lost Souls Downfall prototype.

    The Lost Souls Downfall prototype is free software: you can
    redistribute it and/or modify it under the terms of the GNU
    General Public License as published by the Free Software
    Foundation, either version 3 of the License, or (at your option)
    any later version.

    The Lost Souls Downfall prototype is distributed in the hope that
    it will be useful, but WITHOUT ANY WARRANTY; without even the
    implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
    PURPOSE.  See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with The Lost Souls Downfall prototype.  If not, see
    <http://www.gnu.org/licenses/>.
*/

#ifndef PHYSICS_MOVEMENTCOMPONENT_H
#define PHYSICS_MOVEMENTCOMPONENT_H

#include "../Geometry/Vec3D.h"
#include "../Ecs/Component.h"
#include "../Geometry/PositionComponent.h"

namespace Physics
{
    /**
     * Component for moving entities
     */
    class MovementComponent : public Ecs::Component
    {
    public:
        static const Ecs::Component::Type Type;

        MovementComponent(const Geometry::Vec3Df& velocity):
            Component(Type),
            velocity_(velocity),
            baseVelocity_(velocity)
        {}

        virtual Component* clone() const
        {
            return new MovementComponent(velocity_);
        }

        virtual const std::vector<Ecs::Component::Type>& getDependentComponents()
        {
            if (dependencies_.empty())
            {
                dependencies_.push_back(Geometry::PositionComponent::Type);
            }
            return dependencies_;
        }

        const Geometry::Vec3Df& getVelocity() const
        {
            return velocity_;
        }

        void setVelocity(const Geometry::Vec3Df& velocity)
        {
            velocity_ = velocity;
        }

        const Geometry::Vec3Df& getBaseVelocity() const
        {
            return baseVelocity_;
        }

        void setBaseVelocity(const Geometry::Vec3Df& velocity)
        {
            baseVelocity_ = velocity;
        }

        void setVelocity(const Geometry::Vec2Df& hVelocity)
        {
            velocity_.setHorizontalComponent(hVelocity);
        }

        void setBaseVelocity(const Geometry::Vec2Df& hVelocity)
        {
            baseVelocity_.setHorizontalComponent(hVelocity);
        }

        void resetVerticalVelocity()
        {
            velocity_.setZ(0);
            baseVelocity_.setZ(0);
        }

    private:
        /**
        *   Actual velocity used by the physics engine
        */
        Geometry::Vec3Df velocity_;

        /**
        *   Theoretical velocity from AI/Input
        */
        Geometry::Vec3Df baseVelocity_;

        static std::vector<Ecs::Component::Type> dependencies_;
    };
}
#endif // PHYSICS_MOVEMENTCOMPONENT_H
