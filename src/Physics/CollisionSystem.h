#ifndef PHYSICS_COLLISIONSYSTEM_H
#define PHYSICS_COLLISIONSYSTEM_H

#include "../Ecs/System.h"
#include "../Threading/ThreadableInterface.h"
#include "../Event/EventListenerInterface.h"
#include "../Event/EventManager.h"
#include "MovementTimer.h"
#include "CollisionEngine.h"

namespace Physics
{
    class CollisionSystem : public Ecs::System, public Threading::ThreadableInterface, public Event::EventListenerInterface
    {
        public:
    CollisionSystem(
        Threading::ConcurrentRessource<Ecs::World>& world,
        Event::EventQueue& queue,
        const MovementTimer& timer,
        CollisionEngine& engine
    ):
                Ecs::System(world),
                eventQueue_(queue),
                timer_(timer),
                engine_(engine)
                {}

            virtual void run();
            virtual void call(const Event::Event& event);

        private:
            Event::EventQueue& eventQueue_;
            const MovementTimer& timer_;
            CollisionEngine& engine_;
    };
}

#endif // PHYSICS_COLLISIONSYSTEM_H
