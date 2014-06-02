#include "AiComponent.h"

namespace AI
{
    const Ecs::Component::Type AiComponent::Type = "AiComponent";

    std::vector<Ecs::Component::Type> AiComponent::Dependencies;

    AiComponent::~AiComponent()
    {

        if(aiModule_ !=  NULL)
            delete aiModule_;
    }

}
