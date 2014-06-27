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

#include "HarmComponent.h"

#include "../Physics/CollisionComponent.h"

namespace Character
{
    const Ecs::Component::Type HarmComponent::Type = "harm";
    std::vector<Ecs::Component::Type> HarmComponent::dependentComponents_;

    Ecs::Component* HarmComponent::clone() const
    {
        return new HarmComponent(damages_);
    }

    const std::vector<Ecs::Component::Type>& HarmComponent::getDependentComponents()
    {
        if (dependentComponents_.empty())
        {
            dependentComponents_.push_back(Physics::CollisionComponent::Type);
        }

        return dependentComponents_;
    }

    float HarmComponent::getDamages() const
    {
        return damages_;
    }
}
