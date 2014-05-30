#ifndef GRAPHICS_RENDER_ANIMATIONSYSTEM_H
#define GRAPHICS_RENDER_ANIMATIONSYSTEM_H

#include "../../Ecs/System.h"
#include "../../Event/EventListenerInterface.h"

#include "../../Event/EventManager.h"

using Ecs::World;

namespace Graphics
{
    namespace Render
    {
        // Temporary class for testing purpose
        // TODO: remove and replace by actual Action implementation
        class DummyActionEvent : public Event::Event
        {
        public:
            static const Event::Type TYPE;

            DummyActionEvent(const Ecs::Entity& entity, unsigned int action):
                Event::Event(TYPE),
                entity_(entity),
                action_(action)
                {}

            const Ecs::Entity& getEntity() const
            {
                return entity_;
            }

            const unsigned int& getAction() const
            {
                return action_;
            }

        private:
            Ecs::Entity entity_;
            unsigned int action_;
        };

        class AnimationSystem : public Ecs::System, public Event::EventListenerInterface
        {
        public:
            AnimationSystem(World& world, Event::EventQueue& eventQueue);
            virtual ~AnimationSystem();

            // EventListenerInterface
            virtual void call(const Event::Event& event);
        private:
            Event::EventQueue& eventQueue_;
        };
    }
}

#endif // GRAPHICS_RENDER_ANIMATIONSYSTEM_H
