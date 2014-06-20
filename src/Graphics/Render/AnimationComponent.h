#ifndef GRAPHICS_RENDER_ANIMATIONCOMPONENT_H
#define GRAPHICS_RENDER_ANIMATIONCOMPONENT_H

#include <exception>
#include <map>
#include <vector>
#include "../../Ecs/Component.h"
#include "Animation.h"
#include "RenderableComponent.h"
#include "../../Character/Action.h"

using std::vector;
using std::map;

namespace Graphics
{
    namespace Render
    {
        class NoAnimationDefinedException: public std::exception
        {
            const char* what() const throw()
            {
                return "No animation is defined for this action.";
            }
        };

        class AnimationComponent : public Ecs::Component
        {
        public:
            static const Ecs::Component::Type Type;

            AnimationComponent(const AnimationMap& animationMap, map<Character::Action::Type, AnimationType> animationsByAction):
                Component(Type),
                animationMap_(animationMap),
                animationsByAction_(animationsByAction)
            {}

            virtual Component* clone() const
            {
                return new AnimationComponent(animationMap_, animationsByAction_);
            }

            virtual const std::vector<Ecs::Component::Type>& getDependentComponents()
            {
                if (Dependencies.empty())
                {
                    Dependencies.push_back(RenderableComponent::Type);
                }
                return Dependencies;
            }

            const AnimationMap& getAnimationMap() const
            {
                return animationMap_;
            }

            const AnimationType& getAnimationByAction(Character::Action::Type action)
            {
                if (animationsByAction_.find(action) == animationsByAction_.end())
                    throw new NoAnimationDefinedException();
                else
                    return animationsByAction_[action];
            }

        private:
            AnimationMap animationMap_;
            // TODO : replace unsigned int by a structure for game actions
            map<Character::Action::Type, AnimationType> animationsByAction_;

            static vector<Ecs::Component::Type> Dependencies;
        };
    }
}

#endif // GRAPHICS_RENDER_ANIMATIONCOMPONENT_H
