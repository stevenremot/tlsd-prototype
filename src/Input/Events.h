#ifndef INPUT_EVENTS_H
#define INPUT_EVENTS_H

#include <irrlicht/position2d.h>

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

        CameraEvent(irr::core::position2df cursorPosition):
            Event::Event(TYPE),
            cursorPosition_(cursorPosition)
            {}

        CameraEvent(const CameraEvent& event):
            Event::Event(TYPE),
            cursorPosition_(event.getCursorPosition())
            {}

        const irr::core::position2df& getCursorPosition() const
        {
            return cursorPosition_;
        }

    private:
        irr::core::position2df cursorPosition_;
    };
}

#endif // INPUT_EVENTS_H
