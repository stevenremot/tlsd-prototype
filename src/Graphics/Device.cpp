#include "Device.h"

#include <iostream>
#include <stdexcept>
#include <irrlicht/irrlicht.h>

namespace Graphics
{
    Device::Device() :
        irrlichtDevice_(NULL),
        initialized_(false)
    {
        //ctor
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
            std::cout << "init done" << std::endl;
            return;
        }

        // TODO : render loop
        irrlichtDevice_->run();
        getIrrlichtVideoDriver()->beginScene(true, true, irr::video::SColor(255, 0, 0, 0));

        irrlichtDevice_->getSceneManager()->drawAll();

        getIrrlichtVideoDriver()->endScene();

        // display frames per second in window title
        int fps = getIrrlichtVideoDriver()->getFPS();
        irr::core::stringw str = "FPS :";
        str += fps;
        irrlichtDevice_->setWindowCaption(str.c_str());
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

        // disable mouse cursor
        irrlichtDevice_->getCursorControl()->setVisible(false);

        // TODO : remove
        irr::scene::ISceneNode* cube = irrlichtDevice_->getSceneManager()->addCubeSceneNode();
        cube->setMaterialFlag(irr::video::EMF_LIGHTING,false);
        irrlichtDevice_->getSceneManager()->addCameraSceneNode(0, irr::core::vector3df(0,30,-40), irr::core::vector3df(0,5,0));

        return true;
    }

    irr::video::IVideoDriver* Device::getIrrlichtVideoDriver()
    {
        return irrlichtDevice_->getVideoDriver();
    }
}
