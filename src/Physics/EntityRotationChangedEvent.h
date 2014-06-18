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

#ifndef PHYSICS_ENTITY_ROTATION_CHANGED_EVENT_H
#define PHYSICS_ENTITY_ROTATION_CHANGED_EVENT_H

#include "../Event/Event.h"
#include "../Ecs/Entity.h"
#include "../Geometry/Vec3D.h"

namespace Physics
{
    class EntityRotationChangedEvent: public Event::Event
    {
    public:
        static const Type Type;

        EntityRotationChangedEvent(
            const Ecs::Entity& entity,
            const Geometry::Vec3Df& rotation
        ):
            Event(Type),
            entity_(entity),
            rotation_(rotation)
        {}

        const Ecs::Entity& getEntity()
        {
            return entity_;
        }

        const Geometry::Vec3Df& getRotation()
        {
            return rotation_;
        }

    private:
        Ecs::Entity entity_;
        Geometry::Vec3Df rotation_;
    };

}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
