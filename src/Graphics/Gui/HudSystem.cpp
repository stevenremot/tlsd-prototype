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

#include "HudSystem.h"

#include <iostream> // TODO remove

#include "../../Ecs/ComponentGroup.h"
#include "../../Input/PlayerComponent.h"
#include "../../Character/GroupComponent.h"
#include "../../Character/CharacterComponent.h"
#include "../../Character/GroupUtil.h"
#include "InitGuiEvent.h"
#include "LifeBar.h"

using Threading::getConcurrentReader;
using Threading::ConcurrentReader;
using Character::CharacterComponent;

namespace Graphics
{
    namespace Gui
    {

        void HudSystem::call(const Event::Event& event)
        {
            if (event.getType() == InitGuiEvent::Type)
            {
                const InitGuiEvent& evt = dynamic_cast<const InitGuiEvent&>(event);

                irr::gui::IGUIEnvironment* env = evt.getGuiEnvironment();
                irr::gui::IGUIElement* root = env->getRootGUIElement();

                // Regiser somewhere ?
                LifeBar* lifeBar = new LifeBar(
                    env,
                    root,
                    -1,
                    irr::core::rect<irr::s32>(10, 10, 100, 25)
                );

                lifeBar->setWorld(&getWorldRessource());
            }
        }

        void HudSystem::registerListeners(Event::ListenerRegister& reg)
        {
            reg.put(InitGuiEvent::Type, this);
        }

        void HudSystem::unregisterListeners(Event::ListenerRegister& reg)
        {
            reg.remove(this);
        }
    }
}
