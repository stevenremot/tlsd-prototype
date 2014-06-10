#ifndef MYEVENTRECEIVER_H
#define MYEVENTRECEIVER_H
#include <irrlicht/irrlicht.h>
#include <irrlicht/IEventReceiver.h>
#include <irrlicht/IrrlichtDevice.h>
#include <stdlib.h>
#include <iostream>
#include "GuiId.h"
namespace Graphics
{

void setSkinTransparency(irr::s32 alpha, irr::gui::IGUISkin * skin);

struct SAppContext
{

    irr::IrrlichtDevice *device;
    irr::s32             counter;
    irr::gui::IGUIListBox*    listbox;
};

// TODO Unused function, remove ?
static irr::video::E_DRIVER_TYPE driverChoiceConsole(bool allDrivers=true)
{
    const char* const names[] = {"NullDriver","Software Renderer","Burning's Video","Direct3D 8.1","Direct3D 9.0c","OpenGL 1.x/2.x/3.x"};
    printf("Please select the driver you want:\n");
    irr::u32 i=0;
    for (i=irr::video::EDT_COUNT; i>0; --i)
    {
        if (allDrivers || (irr::IrrlichtDevice::isDriverSupported(irr::video::E_DRIVER_TYPE(i-1))))
            printf(" (%c) %s\n", 'a'+irr::video::EDT_COUNT-i, names[i-1]);
    }

    char c;
    std::cin >> c;
    c = irr::video::EDT_COUNT+'a'-c;

    for (i=irr::video::EDT_COUNT; i>0; --i)
    {
        if (!(allDrivers || (irr::IrrlichtDevice::isDriverSupported(irr::video::E_DRIVER_TYPE(i-1)))))
            --c;
        if ((char)i==c)
            return irr::video::E_DRIVER_TYPE(i-1);
    }
    return irr::video::EDT_COUNT;
}

class MyEventReceiver : public irr::IEventReceiver
{


public:
    MyEventReceiver(SAppContext & context) : Context(context) { }

    virtual bool OnEvent(const irr::SEvent& event)
    {
        if (event.EventType == irr::EET_GUI_EVENT)
        {
            irr::s32 id = event.GUIEvent.Caller->getID();
            irr::gui::IGUIEnvironment* env = Context.device->getGUIEnvironment();

            switch(event.GUIEvent.EventType)
            {
            case irr::gui::EGET_SCROLL_BAR_CHANGED:
                if (id == GUI_ID_TRANSPARENCY_SCROLL_BAR)
                {
                    irr::s32 pos = ((irr::gui::IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
                    setSkinTransparency(pos, env->getSkin());
                }
                break;
            case irr::gui::EGET_BUTTON_CLICKED:
                switch(id)
                {
                case GUI_ID_QUIT_BUTTON:
                    Context.device->closeDevice();
                    return true;

                case GUI_ID_NEW_WINDOW_BUTTON:
                {
                    Context.listbox->addItem(L"Window created");
                    Context.counter += 30;
                    if (Context.counter > 200)
                        Context.counter = 0;

                    irr::gui::IGUIWindow* window = env->addWindow(
                                                       irr::core::rect<irr::s32>(100 + Context.counter, 100 + Context.counter, 300 + Context.counter, 200 + Context.counter),
                                                       false, // modal?
                                                       L"Test window");

                    env->addStaticText(L"Please close me",
                                       irr::core::rect<irr::s32>(35,35,140,50),
                                       true, // border?
                                       false, // wordwrap?
                                       window);
                }
                return true;

                case GUI_ID_FILE_OPEN_BUTTON:
                    Context.listbox->addItem(L"File open");
                    // There are some options for the file open dialog
                    // We set the title, make it a modal window, and make sure
                    // that the working directory is restored after the dialog
                    // is finished.
                    //env->addFileOpenDialog(L"Please choose a file.", true, 0, -1, true);
                    return true;

                default:
                    return false;
                }
                break;

            case irr::gui::EGET_FILE_SELECTED:
            {
                // show the model filename, selected in the file dialog
                irr::gui::IGUIFileOpenDialog* dialog =
                    (irr::gui::IGUIFileOpenDialog*)event.GUIEvent.Caller;
                Context.listbox->addItem(dialog->getFileName());
            }
            break;

            default:
                break;
            }
        }

        return false;
    }

private:
    SAppContext & Context;
};
}
#endif // MYEVENTRECEIVER_H
