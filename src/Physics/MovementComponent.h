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
    using Geometry::Vec3Df;

    /**
     * Component for moving entities
     */
    class MovementComponent : public Ecs::Component
    {
    public:
        static const Ecs::Component::Type Type;

        MovementComponent(const Vec3Df& velocity):
            Component(Type),
            velocity_(velocity)
        {}

        virtual const std::vector<Ecs::Component::Type>& getDependentComponents()
        {
            if (dependencies_.empty())
            {
                dependencies_.push_back(Geometry::PositionComponent::Type);
            }
            return dependencies_;
        }

        const Vec3Df& getVelocity() const
        {
            return velocity_;
        }

        void setVelocity(const Vec3Df& velocity)
        {
            velocity_ = velocity;
        }

    private:
        Vec3Df velocity_;

        static std::vector<Ecs::Component::Type> dependencies_;
    };
}
#endif // PHYSICS_MOVEMENTCOMPONENT_H
