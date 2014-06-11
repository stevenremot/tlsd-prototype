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

#ifndef ECS_ENTITY_DESCRIPTOR_H
#define ECS_ENTITY_DESCRIPTOR_H

#include <vector>

#include "Entity.h"
#include "Component.h"

namespace Ecs
{
    class World;

    /**
     * A class that describes an entity to be added later in the world
     */
    class EntityDescriptor
    {
    public:
        EntityDescriptor():
            entity_(),
            references_(0)
        {}

        ~EntityDescriptor()
        {
            for (unsigned int i = 0; i < components_.size(); i++)
            {
                delete components_[i];
            }
        }

        void addComponent(Component* component)
        {
            components_.push_back(component);
        }

        const std::vector<Component*> getComponents() const
        {
            return components_;
        }

        friend class World;

    private:
        std::vector<Component*> components_;
        Entity entity_;
        unsigned int references_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
