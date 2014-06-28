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

#ifndef CHARACTER_GROUP_CURRENT_HEALTH_CHANGED_EVENT_H
#define CHARACTER_GROUP_CURRENT_HEALTH_CHANGED_EVENT_H

#include "../Event/Event.h"
#include "../Ecs/Entity.h"

namespace Character
{
    /**
     * Dispatched when the current health of a group has changed
     */
    class GroupCurrentHealthChangedEvent: public Event::Event
    {
    public:
        static const Type Type;

        GroupCurrentHealthChangedEvent(const Ecs::Entity& group, unsigned int currentHealth):
            Event(Type),
            group_(group),
            currentHealth_(currentHealth)
        {}

        const Ecs::Entity& getGroup() const
        {
            return group_;
        }

        unsigned int getCurrentHealth() const
        {
            return currentHealth_;
        }

    private:
        Ecs::Entity group_;
        unsigned int currentHealth_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
