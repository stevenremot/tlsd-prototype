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

#ifndef PHYSICS_COLLISIONSYSTEM_H
#define PHYSICS_COLLISIONSYSTEM_H

#include "../Ecs/System.h"
#include "../Threading/ThreadableInterface.h"
#include "../Event/EventListenerInterface.h"
#include "../Event/EventManager.h"
#include "MovementTimer.h"
#include "CollisionEngine.h"

namespace Physics
{
    class CollisionSystem : public Ecs::System, public Threading::ThreadableInterface, public Event::EventListenerInterface
    {
        public:
            CollisionSystem(Ecs::World& world, Event::EventQueue& queue, const MovementTimer& timer, CollisionEngine& engine):
                Ecs::System(world),
                eventQueue_(queue),
                timer_(timer),
                engine_(engine)
                {}

            virtual void run();
            virtual void call(const Event::Event& event);

        private:
            Event::EventQueue& eventQueue_;
            const MovementTimer& timer_;
            CollisionEngine& engine_;
    };
}

#endif // PHYSICS_COLLISIONSYSTEM_H
