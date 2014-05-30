#ifndef GRAPHICS_RENDER_RENDERSYSTEM_H
#define GRAPHICS_RENDER_RENDERSYSTEM_H

#include "../../Ecs/System.h"
#include "../../Event/EventListenerInterface.h"

 #include "../../Event/EventManager.h"

using Ecs::World;

namespace Graphics
{
    namespace Render
    {
        class RenderSystem : public Ecs::System, public Event::EventListenerInterface
        {
        public:
            RenderSystem(World& world, Event::EventQueue& eventQueue);
            virtual ~RenderSystem();

            // EventListenerInterface
            virtual void call(const Event::Event& event);
        private:
            Event::EventQueue& eventQueue_;
        };
    }
}

#endif // GRAPHICS_RENDER_RENDERSYSTEM_H
