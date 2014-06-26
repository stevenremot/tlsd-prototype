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

#ifndef CHARACTER_GROUP_UTIL_H
#define CHARACTER_GROUP_UTIL_H

#include "../Ecs/Entity.h"
#include "../Ecs/World.h"
#include "../Threading/ConcurrentRessource.h"
#include "../Event/EventQueue.h"

namespace Character
{
    void associateToGroup(
        Threading::ConcurrentWriter<Ecs::World>& world,
        const Ecs::Entity& entity,
        const Ecs::Entity& group,
        Event::EventQueue& eventQueue
    );

    unsigned int computeMaxHealth(
        Threading::ConcurrentWriter<Ecs::World>& world,
        const Ecs::Entity& group
    );

    void initGroupHealth(
        Threading::ConcurrentWriter<Ecs::World>& world,
        const Ecs::Entity& group
    );

    bool isPlayerGroup(
        Threading::ConcurrentWriter<Ecs::World>& world,
        const Ecs::Entity& group
    );
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
