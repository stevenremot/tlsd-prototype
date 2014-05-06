#ifndef EVENT_EVENT_LISTENER_INTERFACE_H
#define EVENT_EVENT_LISTENER_INTERFACE_H

#include "Event.h"

namespace Event {

    class EventListenerInterface {
    public:
        virtual void call(const Event & event) = 0;
    };

}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End
