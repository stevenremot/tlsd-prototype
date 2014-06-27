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

#include "EventDeserialization.h"
#include "../Physics/EntityPositionChangedEvent.h"

namespace Network
{
    Geometry::Vec3Df deserializeVec3Df(std::istream& in)
    {
        float x, y, z;
        in >> x >> y >> z;
        return Geometry::Vec3Df(x, y, z);
    }

    Event::Event* deserializeEntityPositionChangedEvent(std::istream& in)
    {
        // TODO entity map
        Ecs::Entity entity;
        in >> entity;
        Geometry::Vec3Df position = deserializeVec3Df(in);
        return new Physics::EntityPositionChangedEvent(entity, position);
    }

    Event::Event* deserializeEvent(std::istream& in)
    {
        std::string token;
        in >> token; // token == "("

        in >> token;

        if (token == Physics::EntityPositionChangedEvent::Type)
        {
            return deserializeEntityPositionChangedEvent(in);
        }


        return NULL;
    }
}
