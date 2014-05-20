#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../Ecs/System.h"
#include "../Threading/ThreadableInterface.h"

using Ecs::System;
using Ecs::World;

namespace Physics
{
  class MovementSystem : public System, public Threading:: ThreadableInterface
    {
    public:
    MovementSystem(World& world) : System(world){}

      virtual void run();
    };
}
#endif // MOVEMENTSYSTEM_H
