#ifndef AISYSTEM_H
#define AISYSTEM_H

#include "../Ecs/System.h"
#include "../Ecs/World.h"

#include "../Threading/ThreadableInterface.h"

/**
 * Ai system manages all the entities which have a Ai component.
 */
namespace AI
{
    class AiSystem : public Ecs::System, public Threading::ThreadableInterface
    {
    public:
        AiSystem(Threading::ConcurrentRessource<Ecs::World>& world) : System(world){}

        virtual void run();
    };
}
#endif // AISYSTEM_H
