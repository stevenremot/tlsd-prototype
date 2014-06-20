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

#ifndef ECS_COMPONENT_H
#define ECS_COMPONENT_H

#include <string>
#include <vector>

namespace Ecs
{
    /**
     * Base class for components.
     *
     * A component represents a certain aspect of an entity.
     * It also handles data for this aspect.
     *
     * Basically, a component always has a type, and can have some data in an
     * arbitrary form. However, these documents may always be serializable, to
     * ease transfer of components on the network.
     */
    class Component
    {
    public:
        /**
         * The type of the type of a component.
         *
         * Every composent should define its type as a static variable
         * named "Type", and inject it to the base Component
         * constructor at instanciation.
         */
        typedef std::string Type;

        Component(Type type): type_(type)
        {}

        virtual ~Component()
        {}

        virtual Component* clone() const = 0;

        /**
         * Return the dependencies of this component
         *
         * Some components require an entity to have other components in
         * order to work. This method tells these component's types.
         */
        virtual const std::vector<Type>& getDependentComponents() = 0;

        /**
         * Returns component's type
         */
        const Type& getType() const
        {
            return type_;
        }

    private:
        Type type_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
