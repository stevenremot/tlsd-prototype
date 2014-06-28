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
#include "../Input/PlayerComponent.h"
#include "../Input/PlayerPositionChangedEvent.h"
#include "GravityComponent.h"
#include "CollisionComponent.h"
#include "EntityPositionChangedEvent.h"

using Geometry::PositionComponent;
using Ecs::World;
using Ecs::Entity;
using Geometry::Vec3Df;

namespace Physics
{
    const Vec3Df GravityVec(0.0, 0.0, -9.81);

    void MovementSystem::run()
    {
        // Get all the entities with movement and position components
        Ecs::ComponentGroup::ComponentTypeCollection types;
        types.insert(MovementComponent::Type);
        types.insert(PositionComponent::Type);

        Ecs::ComponentGroup prototype(types);
        Ecs::World::ComponentGroupCollection groups =
            getWorld()->getComponents(prototype);

        // Update their positions
        timer_->updateCurrentTime();

        if (timer_->getLastTime() > 0)
        {
            unsigned long delay = timer_->getDelay();

            Ecs::World::ComponentGroupCollection::iterator group;
            for (group = groups.begin(); group != groups.end(); ++group)
            {
                Threading::ConcurrentWriter<Ecs::World> world = getWorld();
                Vec3Df movement = getMovement(*world, *group, delay);
                bool hasCollision = world->hasComponent(group->getEntity(), CollisionComponent::Type);
                bool hasInput = world->hasComponent(group->getEntity(), Input::PlayerComponent::Type);

                Threading::ConcurrentWriter<PositionComponent> positionComponent =
                    Threading::getConcurrentWriter<Ecs::Component, PositionComponent>(group->getComponent(PositionComponent::Type));

                positionComponent->setPosition(positionComponent->getPosition() + movement);

                if (!hasCollision)
                    if (movement != Vec3Df(0,0,0))
                    {
                        eventQueue_ << new EntityPositionChangedEvent(group->getEntity(), positionComponent->getPosition());
                    }

                if (hasInput)
                {
                    eventQueue_ << new Input::PlayerPositionChangedEvent(positionComponent->getPosition());
                }
            }
        }

        timer_->updateLastTime();
    }

    Geometry::Vec3Df MovementSystem::getMovement(
        Ecs::World& world,
        Ecs::ComponentGroup& group,
        unsigned long delay
    )
    {
        const Entity& entity = group.getEntity();

        // Must be called before getting any writer to avoid deadlock
        bool hasGravity = world.hasComponent(entity, GravityComponent::Type);

        Threading::ConcurrentRessource<Ecs::Component> movementComponentRessource =
            Threading::ConcurrentRessource<Ecs::Component>(group.getComponent(MovementComponent::Type));

        const float factor = (static_cast<float>(delay) / 1000.0);

        if (hasGravity)
        {
            Threading::ConcurrentReader<GravityComponent> gravityComponent =
                Threading::getConcurrentReader<Ecs::Component, GravityComponent>(world.getEntityComponent(entity, GravityComponent::Type));

            Threading::ConcurrentWriter<MovementComponent> movementComponent =
                Threading::getConcurrentWriter<Ecs::Component, MovementComponent>(movementComponentRessource);

            const Vec3Df& baseVelocity = movementComponent->getVelocity();
            movementComponent->setVelocity(
                baseVelocity +
                GravityVec * gravityComponent->getWeight() * factor
            );
            // add gravity to base velocity
            movementComponent->setBaseVelocity(
                movementComponent->getBaseVelocity() +
                GravityVec * gravityComponent->getWeight() * factor
            );
        }

        return Threading::getConcurrentReader<Ecs::Component, MovementComponent>(movementComponentRessource)->getVelocity() * factor;
    }
}
