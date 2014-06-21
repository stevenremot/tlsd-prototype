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

        CollisionComponent(CollisionBody* collisionBody):
            Ecs::Component(Type),
            collisionBody_(collisionBody)
        {}

        virtual ~CollisionComponent()
        {
            delete collisionBody_;
        }

        virtual Component* clone() const
        {
            return new CollisionComponent(collisionBody_->clone());
        }

        virtual const std::vector<Ecs::Component::Type>& getDependentComponents();

        const CollisionBody& getCollisionBody() const
        {
            return *collisionBody_;
        }

    private:
        static std::vector<Ecs::Component::Type> dependentTypes_;
        CollisionBody* collisionBody_;
    };
}

#endif // PHYSICS_COLLISIONCOMPONENT_H
