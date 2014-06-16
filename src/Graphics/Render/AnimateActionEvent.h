#ifndef GRAPHICS_RENDER_ANIMATEACTIONEVENT_H
#define GRAPHICS_RENDER_ANIMATEACTIONEVENT_H

#include "../../Event/Event.h"
#include "../../Character/Action.h"
#include "../../Ecs/Entity.h"

namespace Graphics
{
    namespace Render
    {
        class AnimateActionEvent : public Event::Event
        {
        public:
            static const Event::Type Type;

            AnimateActionEvent(const Ecs::Entity& entity, const Character::Action::Type& action):
                Event::Event(Type),
                entity_(entity),
                action_(action)
                {}

            const Ecs::Entity& getEntity() const
            {
                return entity_;
            }

            const Character::Action::Type& getAction() const
            {
                return action_;
            }

        private:
            Ecs::Entity entity_;
            Character::Action::Type action_;
        };
    }
}

#endif // GRAPHICS_RENDER_ANIMATEACTIONEVENT_H
