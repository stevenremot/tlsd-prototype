#ifndef INPUT_EVENTS_H
#define INPUT_EVENTS_H

#include "../Geometry/Vec2D.h"

#include "../Event/Event.h"

namespace Input
{
    class MoveEvent : public Event::Event
    {
    public:
        static const Event::Type Type;

        MoveEvent(const Geometry::Vec2Df& dir):
            Event::Event(Type),
            direction_(dir)
            {}

        const Geometry::Vec2Df& getDirection() const
        {
            return direction_;
        }

    private:
        Geometry::Vec2Df direction_;
    };

    class CameraEvent : public Event::Event
    {
    public:
        static const Event::Type Type;

        CameraEvent(const Geometry::Vec2Df& cursorPosition):
            Event::Event(Type),
            cursorPosition_(cursorPosition)
            {}

        CameraEvent(const CameraEvent& event):
            Event::Event(Type),
            cursorPosition_(event.getCursorPosition())
            {}

        const Geometry::Vec2Df& getCursorPosition() const
        {
            return cursorPosition_;
        }

    private:
        Geometry::Vec2Df cursorPosition_;
    };
}

#endif // INPUT_EVENTS_H
