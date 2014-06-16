/*
   This file is part of The Lost Souls Downfall prototype.

    The Lost Souls Downfall prototype is free software: you can
    redistribute it and/or modify it under the terms of the GNU
    General Public License as published by the Free Software
    Foundation, either version 3 of the License, or (at your option)
    any later version.

    The Lost Souls Downfall prototype is distributed in the hope that
    it will be useful, but WITHOUT ANY WARRANTY; without even the
    implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
    PURPOSE.  See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with The Lost Souls Downfall prototype.  If not, see
    <http://www.gnu.org/licenses/>.
*/

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
