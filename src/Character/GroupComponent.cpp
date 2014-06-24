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

#include "GroupComponent.h"
#include <algorithm>

namespace Character
{
    const Ecs::Component::Type GroupComponent::Type = "group";
    const std::vector<Ecs::Component::Type> GroupComponent::dependentComponents_;

    GroupComponent::GroupComponent():
        Component(Type),
        entities_(),
        currentHealth_(0)
    {}

    GroupComponent::GroupComponent(const GroupComponent& group):
        Component(Type),
        entities_(group.entities_),
        currentHealth_(group.currentHealth_)
    {}

    const std::vector<Ecs::Component::Type>& GroupComponent::getDependentComponents()
    {
        return dependentComponents_;
    }

    Ecs::Component* GroupComponent::clone() const
    {
        return new GroupComponent(*this);
    }

    unsigned int GroupComponent::getCurrentHealth() const
    {
        return currentHealth_;
    }

    void GroupComponent::setCurrentHealth(unsigned int currentHealth)
    {
        currentHealth_ = currentHealth;
    }

    const GroupComponent::EntityCollection& GroupComponent::getEntities() const
    {
        return entities_;
    }

    void GroupComponent::addEntity(const Ecs::Entity& entity)
    {
        entities_.insert(entity);
    }

    void GroupComponent::removeEntity(const Ecs::Entity& entity)
    {
        EntityCollection::iterator pos = std::find(
            entities_.begin(),
            entities_.end(),
            entity
        );

        if (pos != entities_.end())
        {
            entities_.erase(pos);
        }
    }
}
