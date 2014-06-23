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

#ifndef INPUT_PLAYER_POSITION_CHANGED_EVENT_H
#define INPUT_PLAYER_POSITION_CHANGED_EVENT_H

#include "../Event/Event.h"
#include "../Geometry/Vec3D.h"

namespace Input
{
    class PlayerPositionChangedEvent: public Event::Event
    {
    public:
        static const Event::Type Type;

        PlayerPositionChangedEvent(const Geometry::Vec3Df& pos):
            Event::Event(Type),
            pos_(pos)
        {}

        const Geometry::Vec3Df& getPosition() const
        {
            return pos_;
        }

    private:
        Geometry::Vec3Df pos_;
    };
};

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
