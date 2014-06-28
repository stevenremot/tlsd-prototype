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
