#ifndef EVENT_EVENT_H
#define EVENT_EVENT_H

#include <string>

namespace Event {

    class Event {
    public:
        typedef std::string Type;
        Event(const Type & type): type_(type)
        {}

        Event (const Event & event): type_(event.type_)
        {}

        virtual ~Event()
        {}

        // virtual std::string serialize() const = 0;

        const Type & getType()const
        {
            return type_;
        }

    private:
        Type type_;
    };

}
#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
