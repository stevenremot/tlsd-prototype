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

#include "UpdateBoot.h"

#include "Application.h"
#include "../Ecs/ComponentCreatedEvent.h"

namespace Application
{
    void UpdateBoot::start()
    {
        Event::EventQueue& queue = getApplication().getEventManager().getEventQueue();

        movementSystem_ = new Physics::MovementSystem(getApplication().getEcsWorld(), queue);

        collisionSystem_ =
            new Physics::CollisionSystem(getApplication().getEcsWorld(), queue, movementSystem_->getTimer());

        std::vector<Threading::ThreadableInterface*> threadables;
        threadables.push_back(movementSystem_);
        threadables.push_back(collisionSystem_);

        setThread(new Threading::Thread(threadables, 120));
        getThread().start();
        finishBoot();
    }
}
