#ifndef GUI_H
#define GUI_H
#include<irrlicht.h>
#include "../../Threading/ThreadableInterface.h"
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif
namespace Graphics
{
    class Gui :
    {
    public:
        Gui();
        virtual ~Gui();
        void Call(void);
    protected:
    private:
        irr::gui::IGUIEnvironment *environment_;

    };
}
#endif // GUI_H
