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

#include "ComponentGroup.h"

#include <stdexcept>

using std::map;
using std::out_of_range;

namespace Ecs
{
    ComponentGroup::ComponentGroup(ComponentTypeCollection types)
    {
        types_ = types;
    }

    ComponentGroup::ComponentGroup(const ComponentGroup & group):
        entity_(group.entity_),
        types_(group.types_),
        components_(group.components_)
    {
    }

    bool ComponentGroup::satisfies(ComponentCollection & components) const
    {
        // Suppose all components have different types
        unsigned int satisfied = 0;

        ComponentCollection::iterator component;
        for (component = components.begin(); component != components.end(); ++component)
        {
            if (types_.find(component->getReader()->getType()) != types_.end())
            {
                satisfied += 1;
            }
        }

        if (satisfied < types_.size())
        {
            return false;
        }

        return true;
    }

    ComponentGroup ComponentGroup::clone(Entity entity, ComponentCollection& components) const
    {
        if (!satisfies(components))
        {
            throw DoesNotSatisfyException();
        }

        ComponentGroup group(*this);
        group.entity_ = entity;

        ComponentCollection::iterator component;
        for (component = components.begin(); component != components.end(); ++component)
        {
            group.components_.insert(
                std::pair<Component::Type, Threading::ConcurrentRessource<Component> >(component->getReader()->getType(), *component)
            );
        }

        return group;
    }
}
