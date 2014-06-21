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
#include "../Physics/GravityComponent.h"
#include "../Physics/MovementSystem.h"
#include "../Threading/Thread.h"
#include "SvgDrawer.h"

namespace PhysicsTest
{
    void testMovementSystem()
    {
        Event::EventManager em;
        Threading::ConcurrentRessource<Ecs::World> world(new Ecs::World(em.getEventQueue()));

        // Concurrent flow, avoid this in the actual code
        Geometry::PositionComponent* pos;

        {
            Threading::ConcurrentWriter<Ecs::World> ww = world.getWriter();
            const Ecs::Entity& entity = ww->createEntity();
            pos = new Geometry::PositionComponent(
                Geometry::Vec3Df()
            );
            ww->addComponent(entity, pos);
            ww->addComponent(
                entity,
                new Physics::MovementComponent(
                    Geometry::Vec3Df(1.0, 0.0, 10.0)
                )
            );
            ww->addComponent(
                entity,
                new Physics::GravityComponent(1)
            );
        }

        Physics::MovementSystem movementSystem(world, em.getEventQueue());

        std::vector<Threading::ThreadableInterface*> threadables;
        threadables.push_back(&em);
        threadables.push_back(&movementSystem);

        Threading::Thread t(threadables, 80);
        t.start();

        Test::SvgDrawer svg(500, 500);
        svg.drawCircle(
            pos->getPosition().getX() * 10,
            -pos->getPosition().getZ() * 10,
            1,
            "red"
        );
        for (unsigned int i = 0; i < 20; i++)
        {
            Threading::sleep(0, 250);
            svg.drawCircle(
                pos->getPosition().getX() * 10,
                -pos->getPosition().getZ() * 10,
                1,
                "red"
            );
        }

        t.stop();

        svg.end();
        std::cout << svg.getContent().str();
    }
}
