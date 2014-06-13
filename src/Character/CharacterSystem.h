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
            CharacterSystem(Ecs::World& world, Event::EventQueue& outsideQueue):
                Ecs::System(world),
                outsideQueue_(outsideQueue)
                {
                    Threading::createChannel(eventQueue_, eventHead_);
                }

            virtual void call(const Event::Event& event);

            virtual void run();

        private:
            Event::EventQueue eventQueue_;
            Event::EventHead eventHead_;

            Event::EventQueue& outsideQueue_;
    };
}

#endif // CHARACTER_CHARACTERSYSTEM_H
