#ifndef INPUT_EVENTS_H
#define INPUT_EVENTS_H

#include "../Event/Event.h"

namespace Input
{
    enum Direction {Forward, Backward, Left, Right};

    class MoveEvent : public Event::Event
    {
    public:
        static const Event::Type TYPE;

        MoveEvent(Direction dir):
            Event::Event(TYPE),
            direction_(dir)
            {}

        Direction getDirection() const
        {
            return direction_;
        }

    private:
        Direction direction_;
    };

    class CameraEvent : public Event::Event
    {
    public:
        static const Event::Type TYPE;

        CameraEvent():
            Event::Event(TYPE)
            {}
    };
}

#endif // INPUT_EVENTS_H
