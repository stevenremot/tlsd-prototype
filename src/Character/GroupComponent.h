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

#ifndef CHARACTER_GROUP_COMPONENT_H
#define CHARACTER_GROUP_COMPONENT_H

#include "../Ecs/Entity.h"
#include "../Ecs/Component.h"

#include <set>

namespace Character
{
    /**
     * Component representing a group of characters.
     *
     * Characters in a group share their life
     *
     * This component may be split in several components later.
     */
    class GroupComponent: public Ecs::Component
    {
    public:
        static const Type Type;
        typedef std::set<Ecs::Entity> EntityCollection;

        GroupComponent();

        virtual const std::vector<Component::Type>& getDependentComponents();
        virtual Component* clone() const;

        unsigned int getCurrentHealth() const;
        void setCurrentHealth(unsigned int currentHealth);

        const EntityCollection& getEntities() const;
        void addEntity(const Ecs::Entity& entity);
        void removeEntity(const Ecs::Entity& entity);

    private:
        GroupComponent(const GroupComponent& group);

        static const std::vector<Component::Type> dependentComponents_;
        EntityCollection entities_;
        unsigned int currentHealth_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
