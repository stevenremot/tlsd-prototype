#include "AnimationComponent.h"

namespace Graphics
{
    namespace Render
    {
        const Ecs::Component::Type Graphics::Render::AnimationComponent::Type = "animation";

        std::vector<Ecs::Component::Type> AnimationComponent::Dependencies;
    }
}
