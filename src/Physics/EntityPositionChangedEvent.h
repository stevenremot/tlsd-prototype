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

#ifndef PHYSICS_ENTITYPOSITIONCHANGED_H
#define PHYSICS_ENTITYPOSITIONCHANGED_H

#include "../Event/Event.h"
#include "../Ecs/Entity.h"
#include "../Geometry/Vec3D.h"

namespace Physics
{
    class EntityPositionChangedEvent : public Event::Event
    {
        public:
            static const Event::Event::Type Type;

            EntityPositionChangedEvent(const Ecs::Entity& entity, const Geometry::Vec3Df& position):
                Event::Event(Type),
                entity_(entity),
                position_(position)
                {}

            const Ecs::Entity& getEntity() const
            {
                return entity_;
            }

            const Geometry::Vec3Df& getPosition() const
            {
                return position_;
            }


        private:
            Ecs::Entity entity_;
            Geometry::Vec3Df position_;

    };
}

#endif // PHYSICS_ENTITYPOSITIONCHANGED_H
