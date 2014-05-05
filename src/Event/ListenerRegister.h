#ifndef EVENT_LISTENER_REGISTER_H
#define EVENT_LISTENER_REGISTER_H

#include <map>
#include <list>

#include "Event.h"
#include "EventListener.h"

namespace Event
{
    class ListenerRegister
    {
    public:
        typedef std::list<EventListener *> EventListenerList;

        void put(EventType type, EventListener * listener);

        const EventListenerList getListeners(EventType type) const;

    private:
        std::map< EventType, EventListenerList > listeners_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End
