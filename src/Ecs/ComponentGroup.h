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

#ifndef ECS_COMPONENT_GROUP_H
#define ECS_COMPONENT_GROUP_H

#include <map>
#include <list>
#include <set>
#include <exception>
#include <stdexcept>

#include "Entity.h"
#include "Component.h"
#include "../Threading/ConcurrentRessource.h"

namespace Ecs
{
    /**
     * Shape of a world's query result.
     *
     * Contain a collection of components of specific types,
     * and the entity associated to these components.
     *
     * It has constraints of the type of components it must contain,
     * so that it can check if the provided components satisfy them.
     */
    class ComponentGroup
    {
    public:
        /**
         * This exception is raised when trying to provide components
         * that do not satisfy types requirements.
         */
        class DoesNotSatisfyException: public std::exception
        {
        public:
            const char * what() const throw()
            {
                return "Tried to clone a group with unsatisfying components.";
            }
        };

        /**
         * This exception is raised when trying to access a component
         * whose type is not in the group.
         */
        class UnexistingComponentException: public std::exception
        {
        public:
            const char * what() const throw()
            {
                return "Tried to get an unexisting component in the group.";
            }
        };

        /**
         * Type to use for sending components to the group methods.
         */
        typedef std::list< Threading::ConcurrentRessource<Component> > ComponentCollection;

        /**
         * Type to use when sending component types to the group methods.
         */
        typedef std::set< Component::Type > ComponentTypeCollection;

        /**
         * Base constructor
         *
         * @param types Component types the group should contain.
         */
        ComponentGroup(ComponentTypeCollection types);
        ComponentGroup(const ComponentGroup& group);

        /**
         * Check if the components satisfies group's types.
         */
        bool satisfies(ComponentCollection& components) const;

        /**
         * Create a new group containing entity and components.
         *
         * The new group has the same requirements than the base one.
         *
         * @throw DoesNotSatisfyException when the components does not match
         *                                the group's requirements
         */
        ComponentGroup clone(Entity entity, ComponentCollection& components) const;

        const Entity& getEntity() const
        {
            return entity_;
        }

        const ComponentTypeCollection& getTypes() const
        {
            return types_;
        }

        /**
         * Return the component of a given type.
         *
         * Be sure to use it on a cloned component group, so that
         * components are defined.
         *
         * @throw UnexistingComponentException if such component does not exist.
         */
        Threading::ConcurrentRessource<Component>& getComponent(Component::Type type)
        {
            try
            {
                return components_.at(type);
            }
            catch (const std::out_of_range& e)
            {
                throw UnexistingComponentException();
            }
        }

    private:
        Entity entity_;
        ComponentTypeCollection types_;
        std::map< Component::Type, Threading::ConcurrentRessource<Component> > components_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
