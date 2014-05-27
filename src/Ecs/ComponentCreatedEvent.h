#ifndef ECS_COMPONENTCREATEDEVENT_H
#define ECS_COMPONENTCREATEDEVENT_H

#include "../Event/Event.h"
#include "Component.h"
#include "Entity.h"

namespace Ecs
{
class ComponentCreatedEvent : public Event::Event
{
    public:
        static const Event::Type TYPE;

        ComponentCreatedEvent(const Entity& entity, Component* component):
            Event::Event(TYPE),
            entity_(entity),
            component_(component)
            {}

        const Entity& getEntity() const
        {
            return entity_;
        }

        const Component* getComponent() const
        {
            return component_;
        }

    private:
        const Entity& entity_;
        Component* component_;
};
}

#endif // ECS_COMPONENTCREATEDEVENT_H
