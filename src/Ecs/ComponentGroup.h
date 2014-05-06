#ifndef ECS_COMPONENT_GROUP_H
#define ECS_COMPONENT_GROUP_H

#include <map>
#include <list>
#include <set>
#include <exception>
#include <stdexcept>

#include "Entity.h"
#include "Component.h"

namespace Ecs
{
    class ComponentGroup
    {
    public:
        class DoesNotSatisfyException: public std::exception
        {
        public:
            const char * what() const throw()
            {
                return "Tried to clone a group with unsatisfying components.";
            }
        };

        class UnexistingComponentException: public std::exception
        {
        public:
            const char * what() const throw()
            {
                return "Tried to get an unexisting component in the group.";
            }
        };

        typedef std::list< Component * > ComponentCollection;
        typedef std::set< Component::Type > ComponentTypeCollection;

        ComponentGroup(ComponentTypeCollection types);
        ComponentGroup(const ComponentGroup & group);

        bool satisfies(const ComponentCollection & components) const;
        ComponentGroup clone(Entity entity, ComponentCollection components) const;

        const Entity & getEntity() const
        {
            return entity_;
        }

        Component & getComponent(Component::Type type)
        {
            try
            {
                return *components_.at(type);
            }
            catch (const std::out_of_range & e)
            {
                throw UnexistingComponentException();
            }
        }

    private:
        Entity entity_;
        std::map< Component::Type, Component * >components_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
