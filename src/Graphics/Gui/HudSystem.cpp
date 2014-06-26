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

#include "../../Character/GroupUtil.h"
#include "../../Character/GroupMaxHealthChangedEvent.h"
#include "../../Character/GroupCurrentHealthChangedEvent.h"
#include "InitGuiEvent.h"

using Character::GroupCurrentHealthChangedEvent;
using Character::GroupMaxHealthChangedEvent;


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

                lifeBar_ = new LifeBar(
                    env,
                    root,
                    -1,
                    irr::core::rect<irr::s32>(10, 10, 100, 25)
                );

                lifeBar_->setCurrentHealth(pendingCurrentHealth_);
                lifeBar_->setMaxHealth(pendingMaxHealth_);
            }
            else if (event.getType() == GroupCurrentHealthChangedEvent::Type)
            {
                const GroupCurrentHealthChangedEvent& evt =
                    dynamic_cast<const GroupCurrentHealthChangedEvent&>(event);

                Threading::ConcurrentWriter<Ecs::World> world = getWorld();
                if (Character::isPlayerGroup(world, evt.getGroup()))
                {
                    if (lifeBar_ == NULL)
                    {
                        pendingCurrentHealth_ = evt.getCurrentHealth();
                    }
                    else
                    {
                        lifeBar_->setCurrentHealth(evt.getCurrentHealth());
                    }
                }
            }
            else if (event.getType() == GroupMaxHealthChangedEvent::Type)
            {
                const GroupMaxHealthChangedEvent& evt =
                    dynamic_cast<const GroupMaxHealthChangedEvent&>(event);

                Threading::ConcurrentWriter<Ecs::World> world = getWorld();
                if (Character::isPlayerGroup(world, evt.getGroup()))
                {
                    if (lifeBar_ == NULL)
                    {
                        pendingMaxHealth_ = evt.getMaxHealth();
                    }
                    else
                    {
                        lifeBar_->setMaxHealth(evt.getMaxHealth());
                    }
                }
            }
        }

        void HudSystem::registerListeners(Event::ListenerRegister& reg)
        {
            reg.put(InitGuiEvent::Type, this);
            reg.put(GroupCurrentHealthChangedEvent::Type, this);
            reg.put(GroupMaxHealthChangedEvent::Type, this);
        }

        void HudSystem::unregisterListeners(Event::ListenerRegister& reg)
        {
            reg.remove(this);
        }
    }
}
