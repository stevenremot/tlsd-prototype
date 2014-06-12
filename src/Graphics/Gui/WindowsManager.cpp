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
*/#include "WindowsManager.h"
namespace Graphics
{
namespace Gui
{
WindowsManager::WindowsManager()
{
    sizex_=640;sizey_=480;
    device_ = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(sizex_, sizey_));

    if (device_ == 0)
    {
        std::cout<<"Impossible to fint the driver OPENGL"<<std::endl;
    }
    device_->setWindowCaption(L"Irrlicht Engine - User Interface Demo");
    device_->setResizable(true);

    driver_ = device_->getVideoDriver();
    env_ = device_->getGUIEnvironment();
    skin_ = env_->getSkin();
    font_ = env_->getFont("media/fonthaettenschweiler.bmp");
    if (font_)
        skin_->setFont(font_);
//****************************************************

// Création de fenetre
    std::vector<Graphics::Gui::Button*> ListeButton;
    std::vector<Graphics::Gui::ScrollBar*> ListeScrollBar;
    std::vector<Graphics::Gui::StaticText*> ListeStatText;
    std::vector<Graphics::Gui::Image*> ListeImage;

    int d=sizey_/10;
    ListeButton.push_back(new Graphics::Gui::Button(irr::core::rect<irr::s32>(sizex_/2-50,20,sizex_/2+50,20 + d),
                          0,
                          GUI_ID_SOLO_BUTTON,
                          L"Solo",
                          0)
                          );
    ListeButton.push_back(new Graphics::Gui::Button(irr::core::rect<irr::s32>(sizex_/2-50,70,sizex_/2+50,70 + d),
                          0,
                          GUI_ID_MULTI_BUTTON,
                          L"Multiplayer",
                          0)
                          );
    ListeButton.push_back(new Graphics::Gui::Button(irr::core::rect<irr::s32>(sizex_/2-50,120,sizex_/2+50,120 + d),
                          0,
                          GUI_ID_OPTION_BUTTON,
                          L"Option",
                          0)
                          );
    ListeButton.push_back(new Graphics::Gui::Button(irr::core::rect<irr::s32>(sizex_/2-50,170,sizex_/2+50,170 + d),
                          0,
                          GUI_ID_CREDITS_BUTTON,
                          L"Credits",
                          0)
                          );
    ListeButton.push_back(new Graphics::Gui::Button(irr::core::rect<irr::s32>(sizex_/2-50,220,sizex_/2+50,220 + d),
                          0,
                          GUI_ID_QUIT_BUTTON,
                          L"Quit",
                          L"Exits Program")
                          );

    Graphics::Gui::Windows* Win=new Graphics::Gui::Windows(device_,env_,driver_,skin_,font_,context_);





    Win->SetComponent(ListeButton,ListeScrollBar,ListeStatText,ListeImage);
    Win->run();
// Affichage des fenetres
    while(device_->run() && driver_)
        if (device_->isWindowActive())
        {
            driver_->beginScene(true, true, irr::video::SColor(0,200,200,200));

            env_->drawAll();

            driver_->endScene();
        }

    device_->drop();
}

WindowsManager::~WindowsManager()
{
    device_=NULL;
    env_=NULL;
    driver_=NULL;
    skin_=NULL;
    font_=NULL;
    context_=NULL;
}

void WindowsManager::Start()
{





}
}
}
