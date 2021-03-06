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

#ifndef ECS_SYSTEM_H
#define ECS_SYSTEM_H

#include "World.h"
#include "../Threading/ConcurrentRessource.h"

namespace Ecs
{
    /**
     * Base class for systems.
     *
     * A system is just an object that can query a World for its components,
     * and may modify them.
     *
     * Try to write one component type with only one system!
     */
    class System
    {
    public:
        System(Threading::ConcurrentRessource<World>& world): world_(world)
        {}

        Threading::ConcurrentWriter<World> getWorld()
        {
            return world_.getWriter();
        }

        Threading::ConcurrentRessource<World>& getWorldRessource()
        {
            return world_;
        }

    private:
        Threading::ConcurrentRessource<World>& world_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
