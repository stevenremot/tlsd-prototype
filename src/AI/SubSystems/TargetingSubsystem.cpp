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

#include "TargetingSubsystem.h"

#include <cfloat>
#include <vector>

#include "../../Geometry/Vec3D.h"

using std::vector;

using Geometry::Vec3Df;

namespace AI
{
    namespace Subsystem
    {

        const Subsystem::SubsystemType TargetingSubsystem::Type = "TargetingSubsystem";

        TargetingSubsystem::TargetingSubsystem(WorkingMemory&memory)
            : Subsystem(Type), memory_(memory), targetId_(-1)
        {
        }

        TargetingSubsystem::~TargetingSubsystem()
        {}

        bool TargetingSubsystem::update(Ecs::ComponentGroup& components)
        {
            MemoryFact::MemoryFactType factType = "sightFact";
            vector<MemoryFact*> ennemyFacts;
            memory_.getMemoryFactsByType(factType, ennemyFacts);
            if (ennemyFacts.size() == 0)
            {
                targetId_ = - 1;
            }
            else
            {
                float currentFactBelief = 0.0;
                float currentDistance = FLT_MAX;
                for(unsigned int i = 0; i < ennemyFacts.size(); i++)
                {
                    MemoryFact * ennemyFact = ennemyFacts[i];
                    float factBelief = ennemyFact->getFactBelief();
                    const Vec3Df& position = ennemyFact->getPosition();
                    float distance = position.getLength();
                    if (currentFactBelief/(FLT_EPSILON + currentDistance) < factBelief/(FLT_EPSILON + distance))
                    {
                        targetId_ = ennemyFact->getCharacterId();
                        currentFactBelief = factBelief;
                        currentDistance = distance;
                    }
                }
            }
            return true;
        }
    }
}
