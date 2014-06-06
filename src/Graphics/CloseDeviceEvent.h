#ifndef GRAPHICS_CLOSEDEVICEEVENT_H
#define GRAPHICS_CLOSEDEVICEEVENT_H

#include "../Event/Event.h"

namespace Graphics
{
    class CloseDeviceEvent : public Event::Event
    {
    public:
        static const Event::Type TYPE;

        CloseDeviceEvent():
            Event::Event(TYPE)
        {}
    };
}

#endif // GRAPHICS_CLOSEDEVICEEVENT_H