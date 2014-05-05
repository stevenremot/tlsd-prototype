#ifndef EVENT_EVENT_MANAGER_H
#define EVENT_EVENT_MANAGER_H

#include "EventQueue.h"
#include "ListenerRegister.h"

namespace Event
{
    class EventManager
    {
    public:
        void run();

        EventQueue & getEventQueue()
        {
            return queue_;
        }

        ListenerRegister & getListenerRegister()
        {
            return listeners_;
        }

    private:
        EventQueue queue_;
        ListenerRegister listeners_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End
