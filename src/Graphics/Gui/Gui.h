#ifndef GUI_H
#define GUI_H
#include <irrlicht.h>
#include <IrrlichtDevice.h>
#include "../../Threading/ThreadableInterface.h"
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif


namespace Graphics
{


class Gui
{
    public:
        Gui();
        virtual ~Gui();
        int Call(void);
    protected:
    private:

};
}
#endif // GUI_H
