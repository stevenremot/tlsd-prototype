#include "ComponentGroup.h"

#include <stdexcept>

using std::map;
using std::out_of_range;

namespace Ecs
{
    ComponentGroup::ComponentGroup(ComponentTypeCollection types)
    {
        ComponentTypeCollection::const_iterator type;
        for (type = types.begin(); type != types.end(); ++type)
        {
            components_[*type] = NULL;
        }
    }

    ComponentGroup::ComponentGroup(const ComponentGroup & group):
        entity_(group.entity_),
        components_(group.components_)
    {
    }

    bool ComponentGroup::satisfies(const ComponentCollection & components) const
    {
        // Suppose all components have different types

        if (components_.size() != components.size())
        {
            return false;
        }

        ComponentCollection::const_iterator component;
        for (component = components.begin(); component != components.end(); ++component)
        {
            try
            {
                components_.at((*component)->getType());
            }
            catch (const out_of_range & e)
            {
                return false;
            }
        }

        return true;
    }

    ComponentGroup ComponentGroup::clone(Entity entity, ComponentCollection components) const
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
            group.components_[(*component)->getType()] = *component;
        }

        return group;
    }
}
