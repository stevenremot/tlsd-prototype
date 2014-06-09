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

#include "MovementSystem.h"

#include "MovementComponent.h"
#include "../Geometry/PositionComponent.h"
#include "../Threading/Thread.h"

using Geometry::PositionComponent;

namespace Physics
{
    void MovementSystem::run()
    {
        World& world = getWorld();

        // Get all the entities with movement and position components
        Ecs::ComponentGroup::ComponentTypeCollection types;
        types.insert(MovementComponent::Type);
        types.insert(PositionComponent::Type);

        Ecs::ComponentGroup prototype(types);
        Ecs::World::ComponentGroupCollection groups = world.getComponents(prototype);

        // Update their positions
        unsigned long currentTime = getCurrentTime();

        if (lastTime_ > 0)
        {
            unsigned long delay = currentTime - lastTime_;

            Ecs::World::ComponentGroupCollection::iterator group;
            for (group = groups.begin(); group != groups.end(); ++group)
            {
                PositionComponent& positionComponent =
                    static_cast<PositionComponent&>(group->getComponent(PositionComponent::Type));
                MovementComponent& movementComponent =
                    static_cast<MovementComponent&>(group->getComponent(MovementComponent::Type));
                Vec3Df offset =
                    movementComponent.getVelocity() *
                    (static_cast<float>(delay) / 1000.0);

                positionComponent.setPosition(positionComponent.getPosition() + offset);
            }
        }

        lastTime_ = currentTime;
    }

    unsigned long MovementSystem::getCurrentTime()
    {
        struct timespec time;
        Threading::getTime(time);
        return time.tv_sec * 1000L + time.tv_nsec / 1000000L;
    }
}
