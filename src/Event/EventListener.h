#ifndef EVENT_EVENT_LISTENER_H
#define EVENT_EVENT_LISTENER_H

#include "Event.h"

namespace Event {

    class EventListener {
    public:
        virtual void call(const Event & event) = 0;
    };

}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End
