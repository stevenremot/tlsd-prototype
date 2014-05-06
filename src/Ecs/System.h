#ifndef ECS_SYSTEM_H
#define ECS_SYSTEM_H

#include "World.h"

namespace Ecs
{
    class System
    {
    public:
        System(World & world): world_(world)
        {}

        World & getWorld()
        {
            return world_;
        }

        const World & getWorld() const
        {
            return world_;
        }

    private:
        World & world_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
