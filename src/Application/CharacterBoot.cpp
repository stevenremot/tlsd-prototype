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
    void CharacterBoot::cleanUp()
    {
        if (characterSystem_ != NULL)
        {
            Event::ListenerRegister& reg =
                getApplication().getEventManager().getListenerRegister();

            characterSystem_->unregisterListeners(reg);
            statSystem_->unregisterListeners(reg);

            delete characterSystem_;
            delete statSystem_;
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

        statSystem_ = new Character::StatSystem(
            getApplication().getEcsWorld(),
            queue
        );
        statSystem_->registerListeners(reg);

        std::vector<Threading::ThreadableInterface*> threadables;
        threadables.push_back(characterSystem_);
        threadables.push_back(statSystem_);

        setThread(new Threading::Thread(threadables, 60));
        getThread().start();
        finishBoot();
    }
}
