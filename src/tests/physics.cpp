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

#include "physics.h"

#include <iostream>

#include "../Geometry/PositionComponent.h"
#include "../Physics/MovementComponent.h"
#include "../Physics/MovementSystem.h"
#include "../Threading/Thread.h"

namespace PhysicsTest
{
    void testMovementSystem()
    {
        Event::EventManager em;
        Ecs::World world(em.getEventQueue());

        const Ecs::Entity& entity = world.createEntity();
        Geometry::PositionComponent* pos = new Geometry::PositionComponent(
            Geometry::Vec3Df()
        );
        world.addComponent(entity, pos);
        world.addComponent(
            entity,
            new Physics::MovementComponent(
                Geometry::Vec3Df(1.0, 0.0, 0.0)
            )
        );

        Physics::MovementSystem movementSystem(world);

        std::vector<Threading::ThreadableInterface*> threadables;
        threadables.push_back(&em);
        threadables.push_back(&movementSystem);

        Threading::Thread t(threadables, 60);
        t.start();

        std::cout << pos->getPosition() << std::endl;
        for (unsigned int i = 0; i < 5; i++)
        {
            Threading::sleep(1, 0);
            std::cout << pos->getPosition() << std::endl;
        }

        t.stop();
    }
}
