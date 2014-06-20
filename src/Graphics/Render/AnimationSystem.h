#ifndef GRAPHICS_RENDER_ANIMATIONSYSTEM_H
#define GRAPHICS_RENDER_ANIMATIONSYSTEM_H

#include "../../Ecs/System.h"
#include "../../Event/EventListenerInterface.h"
#include "../../Threading/Thread.h"

#include "../../Event/EventManager.h"

namespace Graphics
{
    namespace Render
    {
        class AnimationSystem : public Ecs::System, public Event::EventListenerInterface, public Threading::ThreadableInterface
        {
        public:
            AnimationSystem(
                Threading::ConcurrentRessource<Ecs::World>& world,
                Event::EventQueue& outsideQueue
            );
            virtual ~AnimationSystem();

            // EventListenerInterface
            virtual void call(const Event::Event& event);

            // ThreadableInterface
            virtual void run();

            void registerListeners(Event::ListenerRegister& reg);
        private:
            Event::EventQueue eventQueue_;
            Event::EventHead eventHead_;

            Event::EventQueue& outsideQueue_;
        };
    }
}

#endif // GRAPHICS_RENDER_ANIMATIONSYSTEM_H
