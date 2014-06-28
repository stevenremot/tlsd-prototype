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

#include "SensorSystem.h"

#include "SensorComponent.h"
#include "../MemoryComponent.h"
//#include "../AiComponent.h"

using Threading::ConcurrentRessource;
using Threading::ConcurrentReader;
using Threading::ConcurrentWriter;
using Threading::getConcurrentReader;
using Threading::getConcurrentWriter;

namespace AI
{
    namespace Sensor
    {
        void SensorSystem::run()
        {
            // Get all the entities which have a sensor component
            Ecs::ComponentGroup::ComponentTypeCollection types;
            types.insert(SensorComponent::Type);
            types.insert(MemoryComponent::Type);
            Ecs::ComponentGroup prototype(types);
            Ecs::World::ComponentGroupCollection groups = getWorld()->getComponents(prototype);

            // Update their positions
            Ecs::World::ComponentGroupCollection::iterator group;
            for (group = groups.begin(); group != groups.end(); ++group)
            {
                ConcurrentRessource<Ecs::Component> sensorComponentRsr =
                    group->getComponent(SensorComponent::Type);

                ConcurrentRessource<Ecs::Component> memoryComponentRsr =
                    group->getComponent(MemoryComponent::Type);

                getConcurrentWriter<Ecs::Component, MemoryComponent>(
                    memoryComponentRsr
                )->cleanMemory();

                // update all the sensors
                SensorManager& sensorsManager =
                    getConcurrentWriter<Ecs::Component, SensorComponent>(
                        sensorComponentRsr
                    )->getSensorsManager();

                MemoryComponent::MemoryFactsList newFacts = sensorsManager.updateSensors(*getWorld());
                for(unsigned int i = 0; i < newFacts.size(); i++)
                {
                        getConcurrentWriter<Ecs::Component, MemoryComponent>(
                            memoryComponentRsr
                        )->addMemoryFact(newFacts.at(i));
                }
            }
        }
    }
}
