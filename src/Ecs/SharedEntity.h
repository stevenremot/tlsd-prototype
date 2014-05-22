/*
   This file is part of The Lost Souls Downfall prototype.

    The Lost Souls Downfall prototype is free software: you can
    redistribute it and/or modify it under the terms of the GNU
    General Public License as published by the Free Software
    Foundation, either version 3 of the License, or (at your option)
    any later version.

    The Lost Souls Downfall prototype is distributed in the hope that
    it will be useful, but WITHOUT ANY WARRANTY; without even the
    implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
    PURPOSE.  See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with The Lost Souls Downfall prototype.  If not, see
    <http://www.gnu.org/licenses/>.
*/

#ifndef ECS_SHARED_ENTITY_H
#define ECS_SHARED_ENTITY_H

#include "Entity.h"

namespace Ecs
{
    class World;


    /**
     * Represent an entity that must be destroyed when all references disappear
     *
     * Analog to a shared pointer
     */
    class SharedEntity
    {
    public:
        typedef void (*EntityKillCallback)(World&, Entity);

        SharedEntity(World& world, Entity entity, EntityKillCallback killCallback):
            world_(&world),
            entity_(entity),
            killCallback_(killCallback),
            refs_(new unsigned int)
        {
            *refs_ = 1;
        }

        SharedEntity(const SharedEntity& sharedEntity):
            world_(sharedEntity.world_),
            entity_(sharedEntity.entity_),
            killCallback_(sharedEntity.killCallback_),
            refs_(sharedEntity.refs_)
        {
            (*refs_) += 1;
        }

        SharedEntity& operator=(const SharedEntity& sharedEntity)
        {
            unassign();

            world_ = sharedEntity.world_;
            entity_ = sharedEntity.entity_;
            killCallback_ = sharedEntity.killCallback_;
            refs_ = sharedEntity.refs_;

            (*refs_) += 1;

            return *this;
        }

        ~SharedEntity()
        {
            unassign();
        }

        Entity getEntity() const
        {
            return entity_;
        }


    private:
        World* world_;
        Entity entity_;
        EntityKillCallback killCallback_;
        unsigned int* refs_;

        void unassign()
        {
            (*refs_) -= 1;

            if (*refs_ == 0)
            {
                killCallback_(*world_, entity_);
                delete refs_;
            }
        }
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
