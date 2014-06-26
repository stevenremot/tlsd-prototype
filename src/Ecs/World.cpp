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
#include "EntityRemovedEvent.h"

using std::map;

namespace Ecs
{
    template <typename T>
    std::set < T > getIntersection(const std::vector < std::set < T > >& sets)
    {
        std::set<T> intersection;

        const std::set<T>& firstSet = sets[0];
        typename std::set<T>::const_iterator elt;

        for(elt = firstSet.begin(); elt != firstSet.end(); ++elt)
        {
            bool hasEntity = true;
            for (unsigned int i = 1; i < sets.size(); i++)
            {
                if (sets.at(i).find(*elt) == sets.at(i).end())
                {
                    hasEntity = false;
                    break;
                }
            }

            if (hasEntity)
            {
                intersection.insert(*elt);
            }
        }

        return intersection;
    }

    void removeEntity(World& world, Entity entity)
    {
        world.removeEntity(entity);
    }

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

    SharedEntity World::createSharedEntity()
    {
        return shareEntity(createEntity());
    }

    SharedEntity World::createSharedEntity(const Entity& entity)
    {
        return shareEntity(createEntity(entity));
    }

    SharedEntity World::shareEntity(const Entity& entity)
    {
        return SharedEntity(*this, entity, &Ecs::removeEntity);
    }


    bool World::hasEntity(const Entity& entity) const
    {
        return components_.find(entity) != components_.end();
    }

    Entity World::loadDescriptor(EntityDescriptor& descriptor)
    {
        if (descriptor.references_ == 0)
        {
            const Entity& entity = createEntity();

            for (unsigned int i = 0; i < descriptor.getComponents().size(); i++)
            {
                addComponent(entity, descriptor.getComponents()[i]->clone());
            }

            descriptor.entity_ = entity;
        }

        descriptor.references_ += 1;

        return descriptor.entity_;
    }

    void World::unloadDescriptor(EntityDescriptor& descriptor)
    {
        descriptor.references_ -= 1;

        if (descriptor.references_ == 0)
        {
            removeEntity(descriptor.entity_);
        }
    }

    void World::addComponent(const Entity& entity, Component* component)
    {
        ComponentCollection& components = components_.at(entity);
        std::vector<Component::Type> dependencies =
            component->getDependentComponents();

        ComponentCollection::iterator comp;
        for (comp = components.begin(); comp != components.end(); ++comp)
        {
            Component::Type type = comp->getReader()->getType();
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

        entityIndex_[component->getType()].insert(entity);
        components.push_back(component);

        eventQueue_ << new ComponentCreatedEvent(entity, component);
    }

    ComponentGroup World::getEntityComponents(const Entity& entity,
                                              const ComponentGroup& prototype)
    {
        std::map< Entity, ComponentCollection >::iterator pos;
        pos = components_.find(entity);
        if (pos == components_.end())
        {
            throw NoEntityException();
        }

        ComponentCollection& components = pos->second;

        try
        {
            return prototype.clone(entity, components);
        }
        catch (const ComponentGroup::DoesNotSatisfyException& e)
        {
            throw DoesNotSatisfyException();
        }
    }

    Threading::ConcurrentRessource<Component>& World::getEntityComponent(
        const Entity& entity,
        const Component::Type& type
    ) {
        std::map< Entity, ComponentCollection >::iterator pos;
        pos = components_.find(entity);
        if (pos == components_.end())
        {
            throw NoEntityException();
        }

        ComponentCollection& components = pos->second;

        ComponentCollection::iterator component;
        for (component = components.begin(); component != components.end(); ++component)
        {
            if (component->getReader()->getType() == type)
            {
                return *component;
            }
        }

        throw DoesNotSatisfyException();
    }

    World::ComponentGroupCollection World::getComponents(const ComponentGroup& prototype)
    {
        ComponentGroupCollection groups;

        std::vector< std::set < Entity > > entitySets;
        const ComponentGroup::ComponentTypeCollection& types = prototype.getTypes();
        ComponentGroup::ComponentTypeCollection::const_iterator type;
        for (type = types.begin(); type != types.end(); ++type)

        {
            entitySets.push_back(entityIndex_[*type]);
        }

        std::set<Entity> intersection = getIntersection(entitySets);
        std::set<Entity>::iterator entity;

        for (entity = intersection.begin(); entity != intersection.end(); ++entity)
        {
            groups.push_back(prototype.clone(*entity, components_[*entity]));
        }

        return groups;
    }

    void World::removeEntity(const Entity& entity)
    {
        ComponentCollection& components = components_[entity];

        ComponentCollection::iterator component;
        for (component = components.begin(); component != components.end(); ++component)
        {
            entityIndex_[component->getReader()->getType()].erase(entity);
        }

        components_.erase(entity);
        eventQueue_ << new EntityRemovedEvent(entity);
    }

    bool World::hasComponent(const Entity& entity, Component::Type type)
    {
        std::map< Entity, ComponentCollection >::iterator pos;
        pos = components_.find(entity);
        if (pos == components_.end())
        {
            throw NoEntityException();
        }

        return entityIndex_[type].find(entity) != entityIndex_[type].end();
    }
}
