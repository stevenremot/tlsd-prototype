#ifndef TESTS_RENDER_H
#define TESTS_RENDER_H

#include "../Event/Event.h"
#include "../Event/EventListenerInterface.h"

namespace RenderTest
{
    class CloseDeviceListener: public Event::EventListenerInterface
    {
    public:
        CloseDeviceListener():
            closed_(false)
            {}

        virtual void call(const Event::Event &event);
        bool closed_;
    };

    class DummyInputListener: public Event::EventListenerInterface
    {
    public:
        virtual void call(const Event::Event & event);
    };

    void testThread(int durationInSeconds);

    void testRenderSystem(int durationInSeconds);

    void testCamera();
}

#endif // TESTS_RENDER_H
