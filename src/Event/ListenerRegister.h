#ifndef EVENT_LISTENER_REGISTER_H
#define EVENT_LISTENER_REGISTER_H

#include <map>
#include <list>

#include "Event.h"
#include "EventListenerInterface.h"

namespace Event
{
    class ListenerRegister
    {
    public:
        typedef std::list<EventListenerInterface *> EventListenerList;

        void put(Event::Type type, EventListenerInterface * listener);

        const EventListenerList getListeners(Event::Type type) const;

    private:
        std::map< Event::Type, EventListenerList > listeners_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End
