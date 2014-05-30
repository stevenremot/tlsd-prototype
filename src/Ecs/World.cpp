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

#include "World.h"

#include <algorithm>

#include "ComponentCreatedEvent.h"

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

    Entity World::createEntity(const Entity& entity)
    {
        components_[entity] = ComponentCollection();
        return entity;
    }

    void World::addComponent(const Entity& entity, Component* component)
    {
        ComponentCollection& components = components_.at(entity);
        std::vector<Component::Type> dependencies =
            component->getDependentComponents();

        ComponentCollection::const_iterator comp;
        for (comp = components.begin(); comp != components.end(); ++comp)
        {
            Component::Type type = (*comp)->getType();
            if (type == component->getType())
            {
                throw AlreadySetComponentException();
            }

            std::vector<Component::Type>::iterator it =
                std::find(dependencies.begin(), dependencies.end(), type);

            if (it != dependencies.end())
            {
                dependencies.erase(it);
            }
        }

        if (!dependencies.empty())
        {
            throw MissingDependentComponentException();
        }

        components.push_back(component);

        eventQueue_ << new ComponentCreatedEvent(entity, component);
    }

    ComponentGroup World::getEntityComponents(const Entity& entity,
                                              const ComponentGroup& prototype)
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

    bool World::hasComponent(const Entity& entity, Component::Type type) const
    {
        const ComponentCollection& components = components_.at(entity);

        ComponentCollection::const_iterator comp;
        for (comp = components.begin(); comp != components.end(); ++comp)
        {
            if ((*comp)->getType() == type)
                return true;
        }

        return false;
    }
}
