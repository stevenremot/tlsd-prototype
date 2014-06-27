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

#include "Device.h"

#include <iostream>
#include <stdexcept>
#include <irrlicht/irrlicht.h>

#ifdef _WIN32
#else
#include <X11/Xlib.h>
#endif // _WIN32

#include "Render/Scene.h"
#include "Gui/InitGuiEvent.h"
#include "../Input/IrrlichtInputReceiver.h"
#include "CloseDeviceEvent.h"

namespace Graphics
{
    Device::Device(Event::EventQueue& eventQueue) :
        eventQueue_(eventQueue),
        irrlichtDevice_(NULL),
        initialized_(false),
        closed_(false)
    {
#ifdef _WIN32
#else
        XInitThreads();
#endif // _WIN32
    }

    Device::~Device()
    {
        irrlichtDevice_->drop();
    }

    void Device::run()
    {
        if (!initialized_)
        {
            initializeIrrlichtEngine();
            initialized_ = true;
            eventQueue_ << new Render::InitSceneEvent(irrlichtDevice_->getSceneManager(), irrlichtDevice_->getVideoDriver());
            eventQueue_ << new Input::InitInputEvent(irrlichtDevice_->getCursorControl());
            eventQueue_ << new Gui::InitGuiEvent(irrlichtDevice_->getGUIEnvironment());
            std::cout << "[Device]: init done" << std::endl;
            return;
        }


        if (!closed_)
        {
            if (!irrlichtDevice_->run())
            {
                closed_ = true;
                eventQueue_ << new CloseDeviceEvent();
            }

            if (irrlichtDevice_->isWindowFocused())
            {
                getIrrlichtVideoDriver()->beginScene(true, true, irr::video::SColor(255, 0, 0, 0));

                irrlichtDevice_->getSceneManager()->drawAll();
                irrlichtDevice_->getGUIEnvironment()->drawAll();

                getIrrlichtVideoDriver()->endScene();

                // display frames per second in window title
                int fps = getIrrlichtVideoDriver()->getFPS();
                irr::core::stringw str = "FPS :";
                str += fps;
                irrlichtDevice_->setWindowCaption(str.c_str());
            }
        }

    }

    void Device::call(const Event::Event& event)
    {
        irrlichtDevice_->setEventReceiver(static_cast<const Input::InputInitializedEvent&>(event).getReceiver());

        std::cout << "[Input]: Receiver set" << std::endl;
    }

    bool Device::initializeIrrlichtEngine()
    {
        irr::SIrrlichtCreationParameters params;
        // impose OpenGL for cross-platform
        params.DriverType = irr::video::EDT_OPENGL;
        params.WindowSize = irr::core::dimension2d<irr::u32>(800,600);

        //irrlichtDevice_ = irr::createDevice( irr::video::EDT_SOFTWARE, irr::core::dimension2d<irr::u32>(800, 600), 16, false, false, false, 0);
        irrlichtDevice_ = irr::createDeviceEx(params);

        if (irrlichtDevice_ == NULL)
        {
            throw "Couldn't create Irrlicht Device";
        }

        irrlichtDevice_->setResizable(false);

        // disable mouse cursor
        irrlichtDevice_->getCursorControl()->setVisible(false);

        return true;
    }

    irr::video::IVideoDriver* Device::getIrrlichtVideoDriver()
    {
        return irrlichtDevice_->getVideoDriver();
    }
}
