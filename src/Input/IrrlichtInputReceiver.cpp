#include "IrrlichtInputReceiver.h"

namespace Input
{
    using irr::SKeyMap;
    using irr::core::array;
    using irr::core::position2df;

    IrrlichtInputReceiver::IrrlichtInputReceiver(Event::EventQueue& eventQueue):
        eventQueue_(eventQueue)
    {
        createKeyMap();

        // all keys up
        for (irr::u32 i=0; i<irr::EKA_COUNT; i++)
            cursorKeys_[i] = false;
    }

    IrrlichtInputReceiver::~IrrlichtInputReceiver()
    {
        //dtor
    }

    void IrrlichtInputReceiver::call(const Event::Event& event)
    {
        cursorControl_ = static_cast<const InitInputEvent&>(event).getCursorControl();

        if (cursorControl_ != NULL)
        {
            cursorControl_->setPosition(0.5f, 0.5f);
            centerCursor_ = cursorControl_->getRelativePosition();
            cursorPos_ = centerCursor_;
        }
    }

    void IrrlichtInputReceiver::run()
    {

    }

    void IrrlichtInputReceiver::createKeyMap()
    {
        // create default key map
        keyMap_.push_back(SKeyMap(irr::EKA_MOVE_FORWARD, irr::KEY_KEY_Z));
        keyMap_.push_back(SKeyMap(irr::EKA_MOVE_BACKWARD, irr::KEY_KEY_S));
        keyMap_.push_back(SKeyMap(irr::EKA_STRAFE_LEFT, irr::KEY_KEY_Q));
        keyMap_.push_back(SKeyMap(irr::EKA_STRAFE_RIGHT, irr::KEY_KEY_D));
        keyMap_.push_back(SKeyMap(irr::EKA_JUMP_UP, irr::KEY_SPACE));
    }

    bool IrrlichtInputReceiver::OnEvent(const irr::SEvent& event)
    {
        switch(event.EventType)
        {
        case irr::EET_KEY_INPUT_EVENT:
            for (unsigned int i=0; i<keyMap_.size(); ++i)
            {
                if (keyMap_[i].KeyCode == event.KeyInput.Key)
                {
                    cursorKeys_[keyMap_[i].Action] = event.KeyInput.PressedDown;
                    return true;
                }
            }
            break;

        case irr::EET_MOUSE_INPUT_EVENT:
            if (event.MouseInput.Event == irr::EMIE_MOUSE_MOVED)
            {
                cursorPos_ = cursorControl_->getRelativePosition();
                return true;
            }
            /* TODO
            if (event.MouseInput.Event == irr::EMIE_LMOUSE_LEFT_UP)
            {
                actions[0] = true;
                return true;
            }
            if (event.MouseInput.Event == irr::EMIE_RMOUSE_LEFT_UP)
            {
                actions[1] = true;
                return true;
            }
            */
            break;

        default:
            break;
        }

        return false;
    }
}
