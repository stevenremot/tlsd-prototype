#ifndef ECS_WORLD_H
#define ECS_WORLD_H

#include <list>
#include <map>
#include <exception>

#include "Entity.h"
#include "Component.h"
#include "ComponentGroup.h"


namespace Ecs
{
    class World
    {
    public:
        typedef std::list<ComponentGroup> ComponentGroupCollection;

        class DoesNotSatisfyException: public std::exception
        {
        public:
            const char * what() const throw()
            {
                return "Entity's components does not satisfy group requirements.";
            }
        };

        class AlreadySetComponent: public std::exception
        {
            const char * what() const throw()
            {
                return "Trying to add to an entity a component it already has.";
            }
        };

        Entity createEntity();
        Entity createEntity(const Entity & entity);
        void addComponent(const Entity & entity, Component * component);

        ComponentGroup getEntityComponents(
            const Entity & entity,
            const ComponentGroup & prototype
        );

        ComponentGroupCollection getComponents(const ComponentGroup & prototypes);
    private:
        typedef std::list<Component *> ComponentCollection;

        std::map< Entity, ComponentCollection > components_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
