#ifndef GRAPHICS_RENDER_ANIMATIONSYSTEM_H
#define GRAPHICS_RENDER_ANIMATIONSYSTEM_H

#include "../../Ecs/System.h"
#include "../../Event/EventListenerInterface.h"
#include "../../Threading/Thread.h"

#include "../../Event/EventManager.h"

using Ecs::World;

namespace Graphics
{
    namespace Render
    {
        class AnimationSystem : public Ecs::System, public Event::EventListenerInterface, public Threading::ThreadableInterface
        {
        public:
            AnimationSystem(World& world, Event::EventQueue& eventQueue);
            virtual ~AnimationSystem();

            // EventListenerInterface
            virtual void call(const Event::Event& event);

            // ThreadableInterface
            virtual void run();
        private:
            Event::EventQueue& eventQueue_;
        };
    }
}

#endif // GRAPHICS_RENDER_ANIMATIONSYSTEM_H
