#include "ListenerRegister.h"

#include <stdexcept>

using std::out_of_range;

namespace Event
{
    void ListenerRegister::put(Event::Type type, EventListenerInterface * listener)
    {
        listeners_[type].push_back(listener);
    }

    const ListenerRegister::EventListenerList ListenerRegister::getListeners(Event::Type type) const
    {
        try
        {
            return listeners_.at(type);
        }
        catch (const out_of_range & e)
        {
            return EventListenerList();
        }
    }
}
