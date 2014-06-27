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

#ifndef GRAPHICS_RENDER_RENDERSYSTEM_H
#define GRAPHICS_RENDER_RENDERSYSTEM_H

#include "../../Ecs/System.h"
#include "../../Event/EventListenerInterface.h"

#include "../../Event/EventManager.h"

namespace Graphics
{
    namespace Render
    {
        class RenderSystem : public Ecs::System, public Event::EventListenerInterface
        {
        public:
            RenderSystem(Threading::ConcurrentRessource<Ecs::World>& world,
                         Event::EventQueue& eventQueue);
            virtual ~RenderSystem();

            // EventListenerInterface
            virtual void call(const Event::Event& event);
        private:
            Event::EventQueue& eventQueue_;
        };
    }
}

#endif // GRAPHICS_RENDER_RENDERSYSTEM_H
