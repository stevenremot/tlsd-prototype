#ifndef WINDOWSMANAGER_H
#include <irrlicht/irrlicht.h>
#include <stdlib.h>
#include "MyEventReceiver.h"
#include "Windows.h"


namespace Graphics{
    namespace Gui{

class WindowsManager
{
    public:
        WindowsManager();
        virtual ~WindowsManager();
        void Start();
    protected:
    private:
        int sizex_,sizey_;
        irr::IrrlichtDevice * device_;
        irr::gui::IGUIEnvironment* env_;
        irr::video::IVideoDriver* driver_;
        irr::gui::IGUISkin* skin_;
        irr::gui::IGUIFont* font_;
        SAppContext* context_;

};
    }
}
#endif // WINDOWSMANAGER_H
