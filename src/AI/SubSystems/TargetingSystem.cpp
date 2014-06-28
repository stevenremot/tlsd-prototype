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

#include "TargetingSystem.h"

#include <cfloat>

#include "TargetingComponent.h"
#include "../MemoryComponent.h"

using Threading::ConcurrentRessource;
using Threading::ConcurrentReader;
using Threading::ConcurrentWriter;
using Threading::getConcurrentReader;
using Threading::getConcurrentWriter;

namespace AI
{
    namespace Subsystem
    {
        void TargetingSystem::run()
        {
            // Get all the entities which have an ai component

            Ecs::ComponentGroup::ComponentTypeCollection types;
            types.insert(TargetingComponent::Type);
            types.insert(MemoryComponent::Type);
            Ecs::ComponentGroup prototype(types);
            Ecs::World::ComponentGroupCollection groups = getWorld()->getComponents(prototype);

            // Update their positions
            Ecs::World::ComponentGroupCollection::iterator group;
            for (group = groups.begin(); group != groups.end(); ++group)
            {
                try
                {
                    ConcurrentWriter<TargetingComponent> targetingComponent =
                        getConcurrentWriter<Ecs::Component, TargetingComponent>(
                            group->getComponent(TargetingComponent::Type)
                        );
                    ConcurrentWriter<MemoryComponent> memoryComponent =
                        getConcurrentWriter<Ecs::Component, MemoryComponent>(
                            group->getComponent(MemoryComponent::Type)
                        );

                    bool validTarget = false;
                    MemoryFact::MemoryFactType factType = "sightFact";
                    std::vector<MemoryFact*> ennemyFacts;
                    memoryComponent->getMemoryFactsByType(factType, ennemyFacts);
                    if (ennemyFacts.size() != 0)
                    {
                        Ecs::Entity targetEntity;
                        float currentFactBelief = 0.0;
                        float currentDistance = FLT_MAX;
                        for(unsigned int i = 0; i < ennemyFacts.size(); i++)
                        {
                            MemoryFact* ennemyFact = ennemyFacts[i];
                            float factBelief = ennemyFact->getFactBelief();
                            const Geometry::Vec3Df position = ennemyFact->getPosition();
                            float distance = position.getLength();
                            if (currentFactBelief/(FLT_EPSILON + currentDistance) < factBelief/(FLT_EPSILON + distance))
                            {
                                targetEntity = ennemyFact->getCharacterId();
                                currentFactBelief = factBelief;
                                currentDistance = distance;
                                targetingComponent->setTargetPosition(position);
                                targetingComponent->setTargetEntity(targetEntity);
                                //targetingComponent.setHasValidTarget(true);
                                validTarget = true;
                            }
                        }
                    }
                    targetingComponent->setHasValidTarget(validTarget);

                }
                catch (const Ecs::ComponentGroup::UnexistingComponentException& e)
                {
                    continue;
                }

            }
        }
    }
}
