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

#include "IrrlichtInputReceiver.h"

// TODO : remove
#include <iostream>

#include "Events.h"
#include "../Geometry/IrrlichtConversions.h"

using irr::SKeyMap;
using irr::core::array;
using irr::core::position2df;
using Geometry::Vec2Df;

namespace Input
{
    const Event::Event::Type InitInputEvent::Type = "init_input";
    const Event::Event::Type InputInitializedEvent::Type = "input_initialized";

    IrrlichtInputReceiver::IrrlichtInputReceiver(Event::EventQueue& eventQueue):
        cursorControl_(NULL),
        lastDirection_(Vec2Df(0,0)),
        eventQueue_(eventQueue)
    {
        createKeyMap();

        // all keys up
        for (irr::u32 i=0; i<irr::EKA_COUNT; i++)
            cursorKeys_[i] = false;

        actions_[0] = actions_[1] =
            lastActions_[0] = lastActions_[1] = false;
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

            std::cout << "[Input]: Init done" << std::endl;

            eventQueue_ << new InputInitializedEvent(dynamic_cast<irr::IEventReceiver*>(this));
        }
    }

    void IrrlichtInputReceiver::run()
    {
        Vec2Df direction(0,0);

        if (cursorKeys_[irr::EKA_MOVE_FORWARD])
            direction += Vec2Df(1,0);
        if (cursorKeys_[irr::EKA_MOVE_BACKWARD])
            direction += Vec2Df(-1,0);
        if (cursorKeys_[irr::EKA_STRAFE_LEFT])
            direction += Vec2Df(0,-1);
        if (cursorKeys_[irr::EKA_STRAFE_RIGHT])
            direction += Vec2Df(0,1);

        if (direction != lastDirection_)
            eventQueue_ << new MoveEvent(direction);

        lastDirection_ = direction;

        if (cursorControl_ != NULL)
        {
            if (cursorPos_ != centerCursor_)
            {
                eventQueue_ << new CameraEvent(Geometry::fromIrrPosition2df(cursorPos_));

                // Do the fix as normal, special case below
                // reset cursor position to the centre of the window.
                cursorControl_->setPosition(0.5f, 0.5f);
                centerCursor_ = cursorControl_->getRelativePosition();

                // needed to avoid problems when the event receiver is disabled
                cursorPos_ = centerCursor_;
            }
        }

        if (actions_[0] && !lastActions_[0])
        {
            eventQueue_ << new ActionEvent(ActionEvent::LeftActionType);
            lastActions_[0] = true;
        }
        else if (lastActions_[0] && !actions_[0])
        {
            eventQueue_ << new StopActionEvent(StopActionEvent::LeftActionType);
            lastActions_[0] = false;
        }

        if (actions_[1] && !lastActions_[1])
        {
            eventQueue_ << new ActionEvent(ActionEvent::RightActionType);
            lastActions_[1] = true;
        }
        else if (lastActions_[1] && !actions_[1])
        {
            eventQueue_ << new StopActionEvent(StopActionEvent::RightActionType);
            lastActions_[1] = false;
        }
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
            switch (event.MouseInput.Event)
            {
            case irr::EMIE_MOUSE_MOVED:
                cursorPos_ = cursorControl_->getRelativePosition();
                return true;
                break;
            case irr::EMIE_LMOUSE_LEFT_UP:
                actions_[0] = false;
                return true;
                break;
            case irr::EMIE_LMOUSE_PRESSED_DOWN:
                actions_[0] = true;
                return true;
                break;
            case irr::EMIE_RMOUSE_LEFT_UP:
                actions_[1] = false;
                return true;
                break;
            case irr::EMIE_RMOUSE_PRESSED_DOWN:
                actions_[1] = true;
                return true;
                break;
            default:
                break;
            }
            break;

        default:
            break;
        }

        return false;
    }
}
