#ifndef TESTS_ANIMATION_H
#define TESTS_ANIMATION_H

#include "../Event/Event.h"
#include "../Event/EventListenerInterface.h"
#include "../Event/EventManager.h"

namespace AnimationTest
{
    class DummyInputListener: public Event::EventListenerInterface
    {
    public:
        DummyInputListener(Event::EventQueue& eventQueue):
            eventQueue_(eventQueue)
            {}

        virtual void call(const Event::Event & event);

    private:
        Event::EventQueue& eventQueue_;
    };

    void testAnimation();
};

#endif // TESTS_ANIMATION_H
