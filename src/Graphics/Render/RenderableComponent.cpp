#include "RenderableComponent.h"

namespace Graphics
{
    namespace Render
    {
        const Ecs::Component::Type Graphics::Render::RenderableComponent::Type = "renderable";

        std::vector<Ecs::Component::Type> RenderableComponent::Dependencies;
    }
}
