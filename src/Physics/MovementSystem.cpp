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
#include "GravityComponent.h"
#include "CollisionComponent.h"
#include "EntityPositionChangedEvent.h"

using Geometry::PositionComponent;
using Ecs::World;
using Ecs::Entity;

namespace Physics
{
    const Geometry::Vec3Df GravityVec(0.0, 0.0, -9.81);

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
        timer_->updateCurrentTime();

        if (timer_->getLastTime() > 0)
        {
            unsigned long delay = timer_->getDelay();

            Ecs::World::ComponentGroupCollection::iterator group;
            for (group = groups.begin(); group != groups.end(); ++group)
            {
                PositionComponent& positionComponent =
                    dynamic_cast<PositionComponent&>(group->getComponent(PositionComponent::Type));
                Vec3Df movement = getMovement(*group, delay);

                positionComponent.setPosition(positionComponent.getPosition() + movement);

                if (!world.hasComponent(group->getEntity(), CollisionComponent::Type))
                    if (movement != Geometry::Vec3Df(0,0,0))
                        eventQueue_ << new EntityPositionChangedEvent(group->getEntity(), positionComponent.getPosition());
            }
        }

        timer_->updateLastTime();
    }

    Geometry::Vec3Df MovementSystem::getMovement(
        Ecs::ComponentGroup& group,
        unsigned long delay
    )
    {
        World& world = getWorld();

        MovementComponent& movementComponent =
            dynamic_cast<MovementComponent&>(group.getComponent(MovementComponent::Type));
        const float factor = (static_cast<float>(delay) / 1000.0);

        const Entity& entity = group.getEntity();

        if (world.hasComponent(entity, GravityComponent::Type))
        {
            const GravityComponent& gravity = dynamic_cast<GravityComponent&>(
                                                  world.getEntityComponent(entity, GravityComponent::Type)
                                              );

            const Vec3Df& baseVelocity = movementComponent.getVelocity();
            movementComponent.setVelocity(
                baseVelocity +
                GravityVec * gravity.getWeight() * factor
            );
        }

        return movementComponent.getVelocity() * factor;
    }
}
