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

#ifndef CHARACTER_STAT_SYSTEM_H
#define CHARACTER_STAT_SYSTEM_H

#include "../Ecs/System.h"
#include "../Event/EventQueue.h"
#include "../Event/EventListenerInterface.h"
#include "../Threading/ThreadableInterface.h"

namespace Character
{
    class StatSystem: public Ecs::System,
                      public Event::EventListenerInterface,
                      public Threading::ThreadableInterface
    {
    public:
        StatSystem(
            Threading::ConcurrentRessource<Ecs::World>& world,
            const Event::EventQueue& outsideQueue
        ): System(world),
           outsideQueue_(outsideQueue)
        {
            Threading::createChannel(eventQueue_, eventHead_);
        }

        virtual void call(const Event::Event& event);

        virtual void run();

        void registerListeners(Event::ListenerRegister& reg);
        void unregisterListeners(Event::ListenerRegister& reg);

    private:
        Event::EventHead eventHead_;
        Event::EventQueue eventQueue_;
        Event::EventQueue outsideQueue_;
    };

}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
