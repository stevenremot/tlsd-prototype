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

#ifndef GRAPHICS_GUI_LIFE_BAR_H
#define GRAPHICS_GUI_LIFE_BAR_H

#include <irrlicht/IGUIElement.h>

#include "../../Threading/ConcurrentRessource.h"
#include "../../Ecs/World.h"

namespace Graphics
{
    namespace Gui
    {
        /**
         * Temporary life bar widget
         */
        class LifeBar: public irr::gui::IGUIElement
        {
        public:
            LifeBar(irr::gui::IGUIEnvironment* environment,
                    IGUIElement* parent,
                    irr::s32 id,
                    const irr::core::rect<irr::s32>& rect
            ): IGUIElement(irr::gui::EGUIET_ELEMENT, environment, parent, id, rect),
               currentHealth_(0),
               maxHealth_(0)
            {}

            void setCurrentHealth(unsigned int currentHealth)
            {
                currentHealth_ = currentHealth;
            }

            void setMaxHealth(unsigned int maxHealth)
            {
                maxHealth_ = maxHealth;
            }

            virtual void draw();
        private:
            unsigned int currentHealth_;
            unsigned int maxHealth_;
        };
    }
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
