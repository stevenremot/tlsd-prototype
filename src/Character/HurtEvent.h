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

#ifndef CHARACTER_HURT_EVENT_H
#define CHARACTER_HURT_EVENT_H

#include "../Event/Event.h"
#include "../Ecs/Entity.h"

namespace Character
{
    class HurtEvent: public Event::Event
    {
    public:
        static const Type Type;

        HurtEvent(const Ecs::Entity& attacker, const Ecs::Entity& receiver):
            Event(Type),
            attacker_(attacker),
            receiver_(receiver)
        {}

        const Ecs::Entity& getAttacker() const
        {
            return attacker_;
        }

        const Ecs::Entity& getReceiver() const
        {
            return receiver_;
        }

    private:
        Ecs::Entity attacker_;
        Ecs::Entity receiver_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
