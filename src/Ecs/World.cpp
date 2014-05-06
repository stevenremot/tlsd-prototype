#include "World.h"

using std::map;

namespace Ecs
{
    Entity World::createEntity()
    {
        Entity currentId = 0;

        map< Entity, ComponentCollection >::const_iterator pair;
        for (pair = components_.begin(); pair != components_.end(); ++pair)
        {
            if (currentId <= pair->first)
            {
                currentId = pair->first + 1;
            }
        }

        return createEntity(currentId);
    }

    Entity World::createEntity(const Entity & entity)
    {
        components_[entity] = ComponentCollection();
        return entity;
    }

    void World::addComponent(const Entity & entity, Component * component)
    {
        ComponentCollection & components = components_.at(entity);

        ComponentCollection::const_iterator comp;
        for (comp = components.begin(); comp != components.end(); ++comp)
        {
            if ((*comp)->getType() == component->getType())
            {
                throw AlreadySetComponent();
            }
        }

        components.push_back(component);
    }

    ComponentGroup World::getEntityComponents(const Entity & entity,
                                       const ComponentGroup & prototype)
    {
        ComponentCollection & components = components_.at(entity);

        try
        {
            return prototype.clone(entity, components);
        }
        catch (const ComponentGroup::DoesNotSatisfyException & e)
        {
            throw DoesNotSatisfyException();
        }
    }

    World::ComponentGroupCollection World::getComponents(const ComponentGroup & prototype)
    {
        ComponentGroupCollection groups;

        map< Entity, ComponentCollection >::iterator pair;
        for (pair = components_.begin(); pair != components_.end(); ++pair)
        {
            try
            {
                groups.push_back(prototype.clone(pair->first,
                                                 pair->second));
            }
            catch (const ComponentGroup::DoesNotSatisfyException & e)
            {
                continue;
            }
        }

        return groups;
    }
}
