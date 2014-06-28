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

        virtual const std::vector<Ecs::Component::Type>& getDependentComponents()
        {
            return Dependencies;
        }

        virtual Component* clone() const
        {
            return new PositionComponent(position_);
        }

        const Vec3Df & getPosition() const
        {
            return position_;
        }

        void setPosition(const Vec3Df& position)
        {
            position_ = position;
        }

    private:
        Vec3Df position_;
    };
}
#endif // POSITIONCOMPONENT_H
