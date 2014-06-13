#ifndef CHARACTER_CHARACTERSYSTEM_H
#define CHARACTER_CHARACTERSYSTEM_H

#include "../Event/EventListenerInterface.h"
#include "../Event/EventManager.h"
#include "../Ecs/System.h"
#include "../Threading/ThreadableInterface.h"

namespace Character
{
    /**
    *   Receive the ActionPerformedEvents and dispatch it to other systems, while updating the MovementComponent
    */
    class CharacterSystem : public Event::EventListenerInterface, public Ecs::System, public Threading::ThreadableInterface
    {
        public:
            CharacterSystem(Ecs::World& world, Event::EventQueue& eventQueue):
                Ecs::System(world),
                eventQueue_(eventQueue)
                {}

            virtual void call(const Event::Event& event);

            virtual void run();

        private:
            Event::EventQueue& eventQueue_;
            Threading::Channel<Event::Event*> events_;
    };
}

#endif // CHARACTER_CHARACTERSYSTEM_H
