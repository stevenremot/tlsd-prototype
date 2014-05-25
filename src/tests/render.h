#ifndef TESTS_RENDER_H
#define TESTS_RENDER_H

#include "../Event/Event.h"
#include "../Event/EventListenerInterface.h"

namespace RenderTest
{
    class DummyInputListener: public Event::EventListenerInterface
    {
    public:
        virtual void call(const Event::Event & event);
    };

    void testThread();
}

#endif // TESTS_RENDER_H
