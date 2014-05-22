#include "Device.h"

#include <stdexcept>
#include <irrlicht/irrlicht.h>

namespace Graphics
{
    Device::Device() :
        irrlichtDevice_(NULL)
    {
        //ctor
    }

    Device::~Device()
    {
        //dtor
    }

    void Device::run()
    {
        // TODO : render loop
    }

    bool Device::initializeIrrlichtEngine()
    {
        irr::SIrrlichtCreationParameters params;
        // impose OpenGL for cross-platform
        params.DriverType = irr::video::EDT_OPENGL;
        params.WindowSize = irr::core::dimension2d<irr::u32>(800,600);

        irrlichtDevice_ = createDeviceEx(params);

        if (irrlichtDevice_ == NULL)
        {
            throw "Couldn't create Irrlicht Device";
        }

        // disable mouse cursor
        irrlichtDevice_->getCursorControl()->setVisible(false);

        return true;
    }

    irr::video::IVideoDriver* Device::getIrrlichtVideoDriver()
    {
        return irrlichtDevice_->getVideoDriver();
    }
}
