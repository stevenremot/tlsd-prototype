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
using Geometry::Vec2Df;

namespace Physics
{
    Vec2Df getPosition2D(Vec3Df pos)
    {
        return Vec2Df(pos.getX(), pos.getY());
    }

    void CollisionSystem::run()
    {
        // might serve for mesh intersections
        //const float movementFactor =
        //    (static_cast<float>(timer_.getDelay()) / 1000.0);

        // Get all the entities with movement, position and collision component
        ComponentGroup::ComponentTypeCollection types;
        types.insert(MovementComponent::Type);
        types.insert(PositionComponent::Type);
        types.insert(CollisionComponent::Type);

        ComponentGroup prototype(types);
        World::ComponentGroupCollection groups = getWorld()->getComponents(prototype);

        World::ComponentGroupCollection::iterator group;
        for (group = groups.begin(); group != groups.end(); ++group)
        {
            Ecs::Entity movingEntity = group->getEntity();

            Threading::ConcurrentWriter<PositionComponent> positionComponent =
                Threading::getConcurrentWriter<Ecs::Component, PositionComponent>(
                    group->getComponent(PositionComponent::Type)
                );

            // might serve for mesh collisions
            /*Threading::ConcurrentReader<MovementComponent> movementComponent =
                Threading::getConcurrentReader<Ecs::Component, MovementComponent>(
                    group->getComponent(MovementComponent::Type)
                );*/

            Vec3Df positionVector = positionComponent->getPosition();
            // might serve for mesh collisions
            //Vec3Df movementVector = movementComponent->getVelocity() * movementFactor;

            ComponentGroup::ComponentTypeCollection types2;
            types2.insert(CollisionComponent::Type);
            types2.insert(PositionComponent::Type);
            ComponentGroup prototype2(types2);
            World::ComponentGroupCollection groups2 = getWorld()->getComponents(prototype2);
            World::ComponentGroupCollection::iterator group2;
            for (group2 = groups2.begin(); group2 != groups2.end(); ++group2)
            {
                Threading::ConcurrentReader<CollisionComponent> collisionComponent =
                Threading::getConcurrentReader<Ecs::Component, CollisionComponent>(
                    group2->getComponent(CollisionComponent::Type)
                );

                if (collisionComponent->getCollisionBody().getType() == GroundCollisionBody::Type)
                {
                    Threading::ConcurrentReader<PositionComponent> groundPositionComponent =
                        Threading::getConcurrentReader<Ecs::Component, PositionComponent>(
                        group2->getComponent(PositionComponent::Type)
                    );

                    const GroundCollisionBody& collBody =
                        static_cast<const GroundCollisionBody&>(collisionComponent->getCollisionBody());

                    Vec2Df pos2d = getPosition2D(positionVector - groundPositionComponent->getPosition());
                    if (collBody.isOnChunk(pos2d))
                    {
                        float height = collBody.getHeight(pos2d);
                        if (positionVector.getZ() < height)
                        {
                            positionVector.setZ(height);
                            positionComponent->setPosition(positionVector);
                        }
                    }
                }
                // TODO: else
                // if it is a static object, project the movementVector on the ground's plan
            }

            eventQueue_ << new EntityPositionChangedEvent(movingEntity, positionComponent->getPosition());
        }
    }
}
