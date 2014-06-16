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

#include "CollisionSystem.h"

#include "../Ecs/ComponentCreatedEvent.h"
#include "CollisionComponent.h"
#include "MovementComponent.h"
#include "../Geometry/PositionComponent.h"
#include "GroundCollisionBody.h"
#include "EntityPositionChangedEvent.h"

using Ecs::ComponentCreatedEvent;
using Ecs::ComponentGroup;
using Ecs::World;
using Geometry::PositionComponent;
using Geometry::Vec3Df;

namespace Physics
{
    void CollisionSystem::call(const Event::Event& event)
    {
        if (event.getType() == ComponentCreatedEvent::Type)
        {
            const ComponentCreatedEvent& componentEvent = static_cast<const ComponentCreatedEvent&>(event);

            if (componentEvent.getComponentType() == CollisionComponent::Type)
            {
                const Ecs::Entity& entity = componentEvent.getEntity();

                ComponentGroup::ComponentTypeCollection types;
                types.insert(CollisionComponent::Type);

                ComponentGroup prototype(types);
                ComponentGroup group = getWorld().getEntityComponents(entity, prototype);

                const CollisionComponent& positionComponent =
                    static_cast<const CollisionComponent&>(group.getComponent(CollisionComponent::Type));

                if (positionComponent.getCollisionBody().getType() == GroundCollisionBody::Type)
                {
                    engine_.addSelectorCreationCommand(entity);
                }
            }
        }
    }

    void CollisionSystem::run()
    {
        if (!engine_.isInitialized())
            return;

        World& world = getWorld();

        const float movementFactor =
            (static_cast<float>(timer_.getDelay()) / 1000.0);

        // Get all the entities with movement, position and collision component
        ComponentGroup::ComponentTypeCollection types;
        types.insert(MovementComponent::Type);
        types.insert(PositionComponent::Type);
        types.insert(CollisionComponent::Type);

        ComponentGroup prototype(types);
        World::ComponentGroupCollection groups = world.getComponents(prototype);

        World::ComponentGroupCollection::iterator group;
        for (group = groups.begin(); group != groups.end(); ++group)
        {
            Ecs::Entity movingEntity = group->getEntity();
            PositionComponent& positionComponent =
                dynamic_cast<PositionComponent&>(group->getComponent(PositionComponent::Type));
            const MovementComponent& movementComponent =
                dynamic_cast<const MovementComponent&>(group->getComponent(MovementComponent::Type));

            Vec3Df positionVector = positionComponent.getPosition();
            Vec3Df movementVector = movementComponent.getVelocity() * movementFactor;

            ComponentGroup::ComponentTypeCollection types2;
            types2.insert(CollisionComponent::Type);
            ComponentGroup prototype2(types2);
            World::ComponentGroupCollection groups2 = world.getComponents(prototype2);
            World::ComponentGroupCollection::iterator group2;
            for (group2 = groups2.begin(); group2 != groups2.end(); ++group2)
            {
                const CollisionComponent& collisionComponent =
                    dynamic_cast<const CollisionComponent&>(group2->getComponent(CollisionComponent::Type));
                Ecs::Entity collisionEntity = group2->getEntity();

                if (collisionComponent.getCollisionBody().getType() == GroundCollisionBody::Type)
                {
                    if (!engine_.getGroundCollisionResponse(movingEntity, collisionEntity, positionVector, movementVector))
                        positionComponent.setPosition(positionVector);
                }
                // TODO: else
                // if it is a static object, project the movementVector on the ground's plan
            }

            eventQueue_ << new EntityPositionChangedEvent(movingEntity, positionComponent.getPosition());
        }


    }
}
