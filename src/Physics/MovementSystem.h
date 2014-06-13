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

#ifndef PHYSICS_MOVEMENTSYSTEM_H
#define PHYSICS_MOVEMENTSYSTEM_H

#include "../Ecs/System.h"
#include "../Threading/ThreadableInterface.h"
#include "../Geometry/Vec3D.h"
#include "../Event/EventManager.h"
#include "MovementTimer.h"

namespace Physics
{
    class MovementSystem : public Ecs::System, public Threading::ThreadableInterface
    {
    public:
        MovementSystem(Ecs::World& world, Event::EventQueue& eventQueue):
            System(world),
            eventQueue_(eventQueue)
        {
            timer_ = new MovementTimer();
        }

        ~MovementSystem()
        {
            delete timer_;
        }

        virtual void run();

        const MovementTimer& getTimer()
        {
            return *timer_;
        }
    private:
        Event::EventQueue& eventQueue_;
        MovementTimer* timer_;
        Geometry::Vec3Df getMovement(
            Ecs::ComponentGroup& group,
            unsigned long delay
        );
    };
}
#endif // PHYSICS_MOVEMENTSYSTEM_H
