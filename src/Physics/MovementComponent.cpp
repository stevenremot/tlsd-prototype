#include "MovementComponent.h"

namespace Physics
{
  const Ecs::Component::Type MovementComponent::Type = "movement";

  std::vector<Ecs::Component::Type> MovementComponent::Dependencies;
}
