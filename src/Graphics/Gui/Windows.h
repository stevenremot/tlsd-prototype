#ifndef WINDOWS_H
#define WINDOWS_H
#include <irrlicht/irrlicht.h>
#include "MyEventReceiver.h"
#include "Button.h"
#include "Image.h"
#include "ScrollBar.h"
#include "StaticText.h"
#include <vector>



namespace Graphics
{
        namespace Gui{
class Windows
{
public:
    Windows(irr::IrrlichtDevice * device,
            irr::gui::IGUIEnvironment* env,
            irr::video::IVideoDriver* driver,
            irr::gui::IGUISkin* skin,
            irr::gui::IGUIFont* font,
            SAppContext* context);
    void SetComponent(std::vector<Graphics::Gui::Button*> ListeBoutton,
                      std::vector<Graphics::Gui::ScrollBar*> ListeScrollBar,
                      std::vector<Graphics::Gui::StaticText*> ListeStatText,
                      std::vector<Graphics::Gui::Image*> ListeImage);
    virtual ~Windows();
    void run();
protected:
private:
    irr::IrrlichtDevice * device_;
    irr::gui::IGUIEnvironment* env_;
    irr::video::IVideoDriver* driver_;
    irr::gui::IGUISkin* skin_;
    irr::gui::IGUIFont* font_;
    SAppContext* context_;
    std::vector<Graphics::Gui::Button*> ListeBoutton_;
    std::vector<Graphics::Gui::ScrollBar*> ListeScrollBar_;
    std::vector<Graphics::Gui::StaticText*> ListeStatText_;
    std::vector<Graphics::Gui::Image*> ListeImage_;
};
        }
}
#endif // WINDOWS_H
