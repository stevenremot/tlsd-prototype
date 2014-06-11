#include "CollisionComponent.h"
#include "../Geometry/PositionComponent.h"

using Ecs::Component;

namespace Physics
{
    const Component::Type CollisionComponent::Type = "collision";
    std::vector<Component::Type> CollisionComponent::dependentTypes_;

    const std::vector<Component::Type>& CollisionComponent::getDependentComponents()
    {
        if (dependentTypes_.empty())
        {
            dependentTypes_.push_back(Geometry::PositionComponent::Type);
        }
        return dependentTypes_;
    }
}
