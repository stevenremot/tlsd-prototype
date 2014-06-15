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
        static const Event::Type TYPE;

        InitInputEvent(irr::gui::ICursorControl* cursorControl):
            Event::Event(TYPE),
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
        static const Event::Type TYPE;

        InputInitializedEvent(irr::IEventReceiver* receiver):
            Event::Event(TYPE),
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
