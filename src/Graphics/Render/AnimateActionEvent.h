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
