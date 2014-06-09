#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../Ecs/System.h"
#include "../Threading/ThreadableInterface.h"

using Ecs::System;
using Ecs::World;

namespace Physics
{
    class MovementSystem : public System, public Threading::ThreadableInterface
    {
    public:
        MovementSystem(World& world): System(world), lastTime_(0)
        {
        }

        virtual void run();
    private:
        unsigned long lastTime_;
        unsigned long getCurrentTime();
    };
}
#endif // MOVEMENTSYSTEM_H
