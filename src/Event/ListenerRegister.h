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

#ifndef EVENT_LISTENER_REGISTER_H
#define EVENT_LISTENER_REGISTER_H

#include <map>
#include <list>

#include "Event.h"
#include "EventListenerInterface.h"

namespace Event
{
    /**
     * Class that handles associations between event types and listeners.
     */
    class ListenerRegister
    {
    public:
        /**
         * Type of the event lists returns by the query methods.
         */
        typedef std::list<EventListenerInterface*> EventListenerList;

        /**
         * Add an association between an event type and a listener.
         */
        void put(Event::Type type, EventListenerInterface* listener);

        /**
         * Return event listeners associated to type.
         */
        const EventListenerList getListeners(Event::Type type) const;

    private:
        std::map< Event::Type, EventListenerList > listeners_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
