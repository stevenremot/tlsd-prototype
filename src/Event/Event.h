#ifndef EVENT_EVENT_H
#define EVENT_EVENT_H

#include <string>

namespace Event {
    typedef std::string EventType;

    class Event {
    public:
        Event(const EventType & type): type_(type)
        {}

        Event (const Event & event): type_(event.type_)
        {}

        virtual ~Event()
        {}

        // virtual std::string serialize() const = 0;

        const EventType & getType()const
        {
            return type_;
        }

    private:
        EventType type_;
    };

}
#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
