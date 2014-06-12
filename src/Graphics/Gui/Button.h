#ifndef BUTTON_H
#define BUTTON_H
#include <irrlicht/irrlicht.h>
namespace Graphics
{

namespace Gui
{
class Button
{
public:
    Button(irr::core::rect<irr::s32> Rect,
           int i,
           irr::s32 Id,
           const wchar_t* text,
           const wchar_t* tooltiptext):
        Rect_(Rect),i_(i),Id_(Id),text_(text),tooltiptext_(tooltiptext) {}
    virtual ~Button();
    irr::core::rect<irr::s32> GetRect()
    {
        return Rect_ ;
    };
    int GetI()
    {
        return i_;
    };
    irr::s32 GetId()
    {
        return Id_;
    };
    const wchar_t* GetText()
    {
        return text_;
    };
    const wchar_t* GetToolTipText()
    {
        return tooltiptext_;
    };

protected:
private:
    irr::core::rect<irr::s32> Rect_;
    int i_;
    irr::s32 Id_;
    const wchar_t* text_;
    const wchar_t* tooltiptext_;
};
}
}
#endif // BUTTON_H
