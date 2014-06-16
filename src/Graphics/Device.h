#ifndef GRAPHICS_DEVICE_H
#define GRAPHICS_DEVICE_H
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

#include <irrlicht/IrrlichtDevice.h>

#include "../Threading/ThreadableInterface.h"
#include "../Event/EventManager.h"

namespace Graphics
{
    /**
    * This class provides binding with the Irrlicht Graphics Engine's device
    * It also manages the window's initialization
    */
    class Device : public Threading::ThreadableInterface, public Event::EventListenerInterface
    {
    public:
        Device(Event::EventQueue& eventQueue);
        ~Device();

        // Threadable
        virtual void run();

        // Event Listener
        virtual void call(const Event::Event& event);

        bool initializeIrrlichtEngine();
        irr::video::IVideoDriver* getIrrlichtVideoDriver();
    private:
        Event::EventQueue& eventQueue_;

        irr::IrrlichtDevice* irrlichtDevice_;
        bool initialized_, closed_;
    };
}

#endif // GRAPHICS_DEVICE_H
