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
        static const Event::Type Type;

        ComponentCreatedEvent(const Entity& entity, Component* component):
            Event::Event(Type),
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

        const Component::Type getComponentType() const
        {
            return component_->getType();
        }

    private:
        Entity entity_;
        Component* component_;
};
}

#endif // ECS_COMPONENTCREATEDEVENT_H
