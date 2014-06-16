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

#ifndef INPUT_IRRLICHTINPUTRECEIVER_H
#define INPUT_IRRLICHTINPUTRECEIVER_H

#include <irrlicht/IEventReceiver.h>
#include <irrlicht/ICursorControl.h>
#include <irrlicht/SKeyMap.h>
#include <irrlicht/position2d.h>
#include <irrlicht/irrArray.h>

#include "../Event/EventManager.h"
#include "../Threading/ThreadableInterface.h"
#include "../Geometry/Vec2D.h"

namespace Input
{
    /**
    *   Event provided by the Device to initialize the Scene object
    */
    class InitInputEvent : public Event::Event
    {
    public:
        static const Event::Type Type;

        InitInputEvent(irr::gui::ICursorControl* cursorControl):
            Event::Event(Type),
            cursorControl_(cursorControl)
        {}

        irr::gui::ICursorControl* getCursorControl() const
        {
            return cursorControl_;
        }

    private:
        irr::gui::ICursorControl* cursorControl_;
    };

    class InputInitializedEvent : public Event::Event
    {
    public:
        static const Event::Type Type;

        InputInitializedEvent(irr::IEventReceiver* receiver):
            Event::Event(Type),
            receiver_(receiver)
        {}

        irr::IEventReceiver* getReceiver() const
        {
            return receiver_;
        }

    private:
        irr::IEventReceiver* receiver_;
    };

    class IrrlichtInputReceiver : public irr::IEventReceiver, public Event::EventListenerInterface, public Threading::ThreadableInterface
    {
    public:
        IrrlichtInputReceiver(Event::EventQueue& eventQueue);
        virtual ~IrrlichtInputReceiver();

        // EventListener
        virtual void call(const Event::Event& event);

        // Threadable
        virtual void run();

        // IEventReceiver
        virtual bool OnEvent(const irr::SEvent& event);
    protected:
    private:
        void createKeyMap();

        irr::gui::ICursorControl* cursorControl_;

        irr::core::array<irr::SKeyMap> keyMap_;
        irr::core::position2df centerCursor_, cursorPos_;
        bool cursorKeys_[irr::EKA_COUNT];

        Geometry::Vec2Df lastDirection_;

        Event::EventQueue& eventQueue_;
    };
}

#endif // INPUT_IRRLICHTINPUTRECEIVER_H
