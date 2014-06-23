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

#include "CharacterBoot.h"

#include "Application.h"

namespace Application
{
    CharacterBoot::~CharacterBoot()
    {
        if (characterSystem_ != NULL)
        {
            characterSystem_->unregisterListeners(
                getApplication().getEventManager().getListenerRegister()
            );
            delete characterSystem_;
        }
    }

    void CharacterBoot::start()
    {
        Event::ListenerRegister& reg = getApplication().getEventManager().getListenerRegister();
        Event::EventQueue& queue = getApplication().getEventManager().getEventQueue();

        characterSystem_ = new Character::CharacterSystem(
            getApplication().getEcsWorld(),
            queue
        );
        characterSystem_->registerListeners(reg);

        std::vector<Threading::ThreadableInterface*> threadables;
        threadables.push_back(characterSystem_);

        setThread(new Threading::Thread(threadables, 60));
        getThread().start();
        finishBoot();
    }
}
