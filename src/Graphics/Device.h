#ifndef GRAPHICS_DEVICE_H
#define GRAPHICS_DEVICE_H

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
        bool initialized_;
    };
}

#endif // GRAPHICS_DEVICE_H
