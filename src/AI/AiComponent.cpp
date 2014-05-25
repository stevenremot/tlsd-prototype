#include "AiComponent.h"

namespace AI
{
    const Ecs::Component::Type AiComponent::Type = "AiComponent";

    AiComponent::~AiComponent()
    {

        if(aiModule_ !=  NULL)
            delete aiModule_;
    }

}
