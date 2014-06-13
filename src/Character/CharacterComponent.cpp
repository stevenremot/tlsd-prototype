#include "CharacterComponent.h"

namespace Character
{
    const Ecs::Component::Type CharacterComponent::Type = "character";

    std::vector<Ecs::Component::Type> CharacterComponent::Dependencies;
}
