#ifndef GRAPHICS_RENDER_ANIMATIONEVENTS_H
#define GRAPHICS_RENDER_ANIMATIONEVENTS_H

#include "../../Event/Event.h"
#include "Animation.h"
#include "../../Ecs/Entity.h"

namespace Graphics
{
    namespace Render
    {
        class SetupAnimationEvent : public Event::Event
        {
        public:
            static const Event::Type Type;

            SetupAnimationEvent(const AnimationMap& animationMap, const Ecs::Entity& entity):
                Event::Event(Type),
                animationMap_(animationMap),
                entity_(entity)
                {}

            const Ecs::Entity& getEntity() const
            {
                return entity_;
            }

            const AnimationMap& getAnimationMap() const
            {
                return animationMap_;
            }

        private:
            const AnimationMap& animationMap_;
            Ecs::Entity entity_;
        };

        class AnimateEvent : public Event::Event
        {
        public:
            static const Event::Type Type;

            AnimateEvent(const AnimationType& animation, const Ecs::Entity& entity):
                Event::Event(Type),
                animation_(animation),
                entity_(entity)
                {}

            const AnimationType& getAnimation() const
            {
                return animation_;
            }

            const Ecs::Entity& getEntity() const
            {
                return entity_;
            }

        private:
            const AnimationType& animation_;
            Ecs::Entity entity_;
        };

        class UpdateAnimationEvent : public Event::Event
        {
        public:
            static const Event::Type Type;

            UpdateAnimationEvent(const Ecs::Entity& entity):
                Event::Event(Type),
                entity_(entity)
                {}

            const Ecs::Entity& getEntity() const
            {
                return entity_;
            }

        private:
            Ecs::Entity entity_;
        };
    }
}

#endif // GRAPHICS_RENDER_ANIMATIONEVENTS_H
