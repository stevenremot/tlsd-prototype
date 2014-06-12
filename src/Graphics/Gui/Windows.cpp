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
*/#include "Windows.h"


namespace Graphics{
    namespace Gui{
Windows::Windows(irr::IrrlichtDevice * device,
        irr::gui::IGUIEnvironment* env,
        irr::video::IVideoDriver* driver,
        irr::gui::IGUISkin* skin,
        irr::gui::IGUIFont* font,
        SAppContext* context)
{
    device_=device;
    env_=env;
    driver_=driver;
    skin_=skin;
    font_=font;
    context_=context;
}

Windows::~Windows()
{
    //dtor
}
void Windows::SetComponent(std::vector<Graphics::Gui::Button*> ListeBoutton,
                          std::vector<Graphics::Gui::ScrollBar*> ListeScrollBar,
                          std::vector<Graphics::Gui::StaticText*> ListeStatText,
                          std::vector<Graphics::Gui::Image*> ListeImage)
                          {
                         ListeBoutton_=ListeBoutton;
                         ListeScrollBar_=ListeScrollBar;
                         ListeStatText_=ListeStatText;
                         ListeImage_=ListeImage;
                          }
void Windows::run(){

env_->clear();

for(int i=0;i<ListeBoutton_.size();i++){
env_->addButton(ListeBoutton_[i]->GetRect(),0,ListeBoutton_[i]->GetId(),ListeBoutton_[i]->GetText(),ListeBoutton_[i]->GetToolTipText());
}
/*
for(int i=0;i<ListeScrollBar_->size();i++){
//env_->addButton(ListeScrollBar_[i]);
}
for(int i=0;i<ListeStatText_->size();i++){
//env_->addButton(ListeStatText_[i]);
}
for(int i=0;i<ListeImage_->size();i++){
//env_->addButton(ListeImage_[i]);
}
*/
}
}
}
