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
#include "MyEventReceiver.h"
#include "Gui.h"
namespace Graphics
{

Gui::Gui()
{
}

Gui::~Gui()
{
    //dtor
}

int Gui::Call()
{
    int compteur=0;

    irr::IrrlichtDevice * device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(640, 480));

    if (device == 0)
        return 1; // could not create selected driver.
    device->setWindowCaption(L"Irrlicht Engine - User Interface Demo");
    device->setResizable(true);

    irr::video::IVideoDriver* driver = device->getVideoDriver();
    irr::gui::IGUIEnvironment* env = device->getGUIEnvironment();
    irr::gui::IGUISkin* skin = env->getSkin();
    irr::gui::IGUIFont* font = env->getFont("media/fonthaettenschweiler.bmp");

    if (font)
        skin->setFont(font);

    skin->setFont(env->getBuiltInFont(),irr::gui::EGDF_TOOLTIP);
// ajout de bouton
    env->addButton(irr::core::rect<irr::s32>(10,240,110,240 + 32), 0, GUI_ID_QUIT_BUTTON,
                   L"Quit", L"Exits Program");

    env->addButton(irr::core::rect<irr::s32>(10,280,110,280 + 32), 0, GUI_ID_NEW_WINDOW_BUTTON,
                   L"New Window", L"Launches a new Window");

    env->addButton(irr::core::rect<irr::s32>(10,320,110,320 + 32), 0, GUI_ID_FILE_OPEN_BUTTON,
                   L"File Open", L"Opens a file");
// ajout du texte
    env->addStaticText(L"Transparent Control:", irr::core::rect<irr::s32>(150,20,350,40), true);

// ajout de scroll bar
    irr::gui::IGUIScrollBar* scrollbar = env->addScrollBar(true,
                                         irr::core::rect<irr::s32>(150, 45, 350, 60), 0, GUI_ID_TRANSPARENCY_SCROLL_BAR);
    scrollbar->setMax(255);
    scrollbar->setPos(255);
    setSkinTransparency( scrollbar->getPos(), env->getSkin());

    // set scrollbar position to alpha value of an arbitrary element
    scrollbar->setPos(env->getSkin()->getColor(irr::gui::EGDC_WINDOW).getAlpha());

    env->addStaticText(L"Logging ListBox:", irr::core::rect<irr::s32>(50,110,250,130), true);
    irr::gui::IGUIListBox * listbox = env->addListBox(irr::core::rect<irr::s32>(50, 140, 250, 210));
    env->addEditBox(L"Editable Text", irr::core::rect<irr::s32>(350, 80, 550, 100));

    // Store the appropriate data in a context structure.
    SAppContext context;
    context.device = device;
    context.counter = 0;
    context.listbox = listbox;

    // Then create the event receiver, giving it that context structure.
    MyEventReceiver receiver(context);

    // And tell the device to use our custom event receiver.
    device->setEventReceiver(&receiver);
    env->addImage(driver->getTexture("media/irrlichtlogo2.png"), irr::core::position2d<int>(10,10));



    // Affichage de la fenêtre!
    while(device->run() && driver)
        if (device->isWindowActive())
        {
            driver->beginScene(true, true, irr::video::SColor(0,200,200,200));

            env->drawAll();

            driver->endScene();
        }

    device->drop();

    return 0;
}
}

