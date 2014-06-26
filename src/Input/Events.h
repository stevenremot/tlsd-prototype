/*
   This file is part of The Lost Souls Downfall prototype.

    The Lost Souls Downfall prototype is free software: you can
    redistribute it and/or modify it under the terms of the GNU
    General Public License as published by the Free Software
    Foundation, either version 3 of the License, or (at your option)
    any later version.

    The Lost Souls Downfall prototype is distributed in the hope that
    it will be useful, but WITHOUT ANY WARRANTY; without even the
    implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
    PURPOSE.  See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with The Lost Souls Downfall prototype.  If not, see
    <http://www.gnu.org/licenses/>.
*/

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

    class ActionEvent: public Event::Event
    {
    public:
        static const Type Type;
        enum ActionType { LeftActionType, RightActionType };

        ActionEvent(const ActionType& type):
            Event(Type),
            type_(type)
        {}

        const ActionType& getType() const
        {
            return type_;
        }

    private:
        ActionType type_;
    };

    class StopActionEvent: public Event::Event
    {
    public:
        static const Type Type;
        enum ActionType { LeftActionType, RightActionType };

        StopActionEvent(const ActionType& type):
            Event(Type),
            type_(type)
        {}

        const ActionType& getType() const
        {
            return type_;
        }

    private:
        ActionType type_;
    };
}

#endif // INPUT_EVENTS_H

// Emacs local variables
// Local variables:
// mode: c++
// End:
