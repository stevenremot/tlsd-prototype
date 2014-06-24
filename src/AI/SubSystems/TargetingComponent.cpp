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

#include "TargetingComponent.h"
namespace AI
{
    namespace Subsystem
    {
        const Ecs::Component::Type TargetingComponent::Type = "targeting";

        std::vector<Ecs::Component::Type> TargetingComponent::Dependencies;

        bool TargetingComponent::isTargetValid(const Geometry::Vec3Df& targetPosition) const
        {
            return hasValidTarget_ && ((targetPosition - targetPosition_).getLength() < 5.0f);
        }
    }
}
