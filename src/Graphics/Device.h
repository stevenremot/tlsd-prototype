#ifndef GRAPHICS_DEVICE_H
#define GRAPHICS_DEVICE_H

#include <irrlicht/IrrlichtDevice.h>

#include "../Threading/ThreadableInterface.h"


namespace Graphics
{
    /**
    * This class provides binding with the Irrlicht Graphics Engine's device
    * It also manages the window's initialization
    */
    class Device : public Threading::ThreadableInterface
    {
    public:
        Device();
        ~Device();

        // override
        virtual void run();

        bool initializeIrrlichtEngine();
        irr::video::IVideoDriver* getIrrlichtVideoDriver();
    private:
        irr::IrrlichtDevice* irrlichtDevice_;
    };
}

#endif // GRAPHICS_DEVICE_H
