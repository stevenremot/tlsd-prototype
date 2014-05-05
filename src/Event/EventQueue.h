#ifndef EVENT_EVENT_QUEUE_H
#define EVENT_EVENT_QUEUE_H

#include <list>

#include "Event.h"

namespace Event {

    class EventQueue {
    public:
        void push(const Event * event);
        const Event * pop();
    private:
        std::list<const Event *> events_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End
