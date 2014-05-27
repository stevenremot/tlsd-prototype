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

#ifndef ECS_WORLD_H
#define ECS_WORLD_H

#include <list>
#include <map>
#include <exception>

#include "Entity.h"
#include "Component.h"
#include "ComponentGroup.h"

#include "../Event/EventManager.h"


namespace Ecs
{
    /**
     * Class that registers association between entities and components.
     *
     * These associations can then be queried.
     *
     * The queries uses a prototype ComponentGroup to define the shape and
     * the requirements about whar is expected in return.
     */
    class World
    {
    public:
        /**
         * The type returned by request for multiple entities.
         */
        typedef std::list<ComponentGroup> ComponentGroupCollection;

        /**
         * This exception is raised when the components of an entity are asked
         * using a wrong component group as prototype.
         */
        class DoesNotSatisfyException: public std::exception
        {
        public:
            const char* what() const throw()
            {
                return "Entity's components does not satisfy group requirements.";
            }
        };

        class MissingDependentComponentException: public std::exception
        {
        public:
            const char* what() const throw()
            {
                return "Attempted to add to add a component with unsatisfied dependencies";
            }
        };

        /**
         * This exception is raised when someone try to add a composant to
         * an entity which is already associated to this kind of component.
         */
        class AlreadySetComponentException: public std::exception
        {
            const char * what() const throw()
            {
                return "Trying to add to an entity a component it already has.";
            }
        };

        /**
         *  Initialize the World by giving it a reference to the eventQueue
         *
         */
         World(Event::EventQueue eventQueue):
             eventQueue_(eventQueue)
             {}

        /**
         * Create a new entity with no components.
         *
         * The entity has an arbitrary value. Do not use it on the client, where
         * entities may be synchronized with the server.
         */
        Entity createEntity();

        /**
         * Register a new entity in the database.
         *
         * Prepare the world to receive components for entity.
         *
         * Use it for synchronizations with the server.
         */
        Entity createEntity(const Entity & entity);

        /**
         * Add an association between an entity and a component.
         *
         * @throw AlreadySetComponentException when entity is already associated
         *                                     with a component of the same type
         */
        void addComponent(const Entity & entity, Component * component);

        /**
         * Return a ComponentGroup filled with entity and matching components.
         *
         * @throw DoesNotSatisfyException when entity's components does not match
         *                                prototype.
         */
        ComponentGroup getEntityComponents(
            const Entity & entity,
            const ComponentGroup & prototype
        );

        /**
         * Return components groups for entities matching prototype.
         */
        ComponentGroupCollection getComponents(const ComponentGroup & prototypes);

    private:
        typedef std::list<Component *> ComponentCollection;

        std::map< Entity, ComponentCollection > components_;

        Event::EventQueue& eventQueue_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
