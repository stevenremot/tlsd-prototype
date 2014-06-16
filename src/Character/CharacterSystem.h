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

#ifndef CHARACTER_CHARACTERSYSTEM_H
#define CHARACTER_CHARACTERSYSTEM_H

#include "../Event/EventListenerInterface.h"
#include "../Event/EventManager.h"
#include "../Ecs/System.h"
#include "../Threading/ThreadableInterface.h"

namespace Character
{
    /**
    *   Receive the ActionPerformedEvents and dispatch it to other systems, while updating the MovementComponent
    */
    class CharacterSystem : public Event::EventListenerInterface, public Ecs::System, public Threading::ThreadableInterface
    {
        public:
            CharacterSystem(Ecs::World& world, Event::EventQueue& outsideQueue):
                Ecs::System(world),
                outsideQueue_(outsideQueue)
                {
                    Threading::createChannel(eventQueue_, eventHead_);
                }

            virtual void call(const Event::Event& event);

            virtual void run();

            void registerListeners(Event::ListenerRegister& reg);

        private:
            Event::EventQueue eventQueue_;
            Event::EventHead eventHead_;

            Event::EventQueue& outsideQueue_;
    };
}

#endif // CHARACTER_CHARACTERSYSTEM_H
