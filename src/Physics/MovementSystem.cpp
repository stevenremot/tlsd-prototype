#include "MovementSystem.h"

#include "MovementComponent.h"
#include "../Geometry/PositionComponent.h"

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
        Ecs::World::ComponentGroupCollection::iterator group;
        for (group = groups.begin(); group != groups.end(); ++group)
        {
            PositionComponent & positionComponent = static_cast<PositionComponent &>(group->getComponent(PositionComponent::Type));
            MovementComponent & movementComponent = static_cast<MovementComponent &>(group->getComponent(MovementComponent::Type));
            positionComponent.setPosition(positionComponent.getPosition() + movementComponent.getVelocity());
        }
    }
}
 
