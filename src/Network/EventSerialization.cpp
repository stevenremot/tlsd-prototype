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

#include "EventSerialization.h"

#include "../Physics/EntityPositionChangedEvent.h"

namespace Network
{
    bool serializeEvent(
        std::ostream& out,
        const Physics::EntityPositionChangedEvent& event
    ) {
        out << "( " << event.getType() << " " <<
            event.getEntity() << " " <<
            event.getPosition() << " )";
        return true;
    }

    bool serializeEvent(std::ostream& out, const Event::Event& event)
    {
        if (event.getType() == Physics::EntityPositionChangedEvent::Type)
        {
            return serializeEvent(
                out,
                dynamic_cast<const Physics::EntityPositionChangedEvent&>(event)
            );
        }

        return false;
    }
}
