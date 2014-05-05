#include "EventQueue.h"

namespace Event
{
    using std::list;

    void EventQueue::push(const Event * event)
    {
        events_.push_back(event);
    }

    const Event * EventQueue::pop()
    {
        if (events_.empty())
        {
            return NULL;
        }

        const Event * event = events_.front();
        events_.pop_front();
        return event;
    }
}
