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

#ifndef EVENT_EVENT_QUEUE_H
#define EVENT_EVENT_QUEUE_H

#include <list>

#include "Event.h"
#include "../Threading/Channel.h"

namespace Event
{
    /**
     * Represent a queue of events
     *
     * New events can be added to it.
     */
    typedef Threading::ChannelInput<Event*> EventQueue;

    /**
     * Receive the events sent to the event queue
     */
    typedef Threading::ChannelOutput<Event*> EventHead;
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End
