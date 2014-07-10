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

#ifndef GRAPHICS_GUI_HUD_SYSTEM_H
#define GRAPHICS_GUI_HUD_SYSTEM_H

#include <irrlicht/IVideoDriver.h>

#include "../../Ecs/System.h"
#include "../../Event/EventListenerInterface.h"
#include "../../Event/ListenerRegister.h"
#include "LifeBar.h"

namespace Graphics
{
    namespace Gui
    {
        /**
         * System for displaying HUD
         *
         * Temporary implementation
         */
        class HudSystem: public Ecs::System,
                         public Event::EventListenerInterface
        {
        public:
            HudSystem(Threading::ConcurrentRessource<Ecs::World>& world):
                System(world),
                lifeBar_(NULL),
                pendingMaxHealth_(0),
                pendingCurrentHealth_(0)
            {}

            ~HudSystem()
            {
                if (lifeBar_ != NULL)
                {
                    delete lifeBar_;
                }
            }

            virtual void call(const Event::Event& event);

            void registerListeners(Event::ListenerRegister& reg);
            void unregisterListeners(Event::ListenerRegister& reg);

        private:
            LifeBar* lifeBar_;
            unsigned int pendingMaxHealth_;
            unsigned int pendingCurrentHealth_;
        };
    }
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
