#ifndef CHARACTER_CHARACTERCOMPONENT_H
#define CHARACTER_CHARACTERCOMPONENT_H

#include "../Ecs/Component.h"
#include "../Graphics/Render/AnimationComponent.h"

namespace Character
{

    /**
    *   Component which describes a game character
    */
    class CharacterComponent : public Ecs::Component
    {
    public:
        static const Ecs::Component::Type Type;

        static std::vector<Ecs::Component::Type> Dependencies;

        CharacterComponent(float walkingSpeed):
            Component(Type),
            walkingSpeed_(walkingSpeed)
        {}

        virtual const std::vector<Ecs::Component::Type>& getDependentComponents()
        {
            if (Dependencies.empty())
            {
                Dependencies.push_back(Graphics::Render::AnimationComponent::Type);
            }
            return Dependencies;
        }

        float getWalkingSpeed() const
        {
            return walkingSpeed_;
        }

    private:
        float walkingSpeed_;
    };
}

#endif // CHARACTER_CHARACTERCOMPONENT_H
