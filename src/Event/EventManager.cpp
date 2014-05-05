#include "EventManager.h"

namespace Event
{
    void EventManager::run()
    {
        const Event * event = queue_.pop();
        if (event != NULL)
        {
            const ListenerRegister::EventListenerList & listeners = listeners_.getListeners(event->getType());

            ListenerRegister::EventListenerList::const_iterator listener;
            for (listener = listeners.begin(); listener != listeners.end(); ++listener)
            {
                (*listener)->call(*event);
            }

            delete event;
        }
    }
}
