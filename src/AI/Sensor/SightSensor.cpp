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

#include "SightSensor.h"

#include <vector>

#include "../../Ecs/ComponentGroup.h"
#include "../../Geometry/PositionComponent.h"
#include "../../Physics/MovementComponent.h"

using std::max;
using std::vector;

using Geometry::PositionComponent;
using Geometry::Vec3Df;

using Physics::MovementComponent;

using Threading::ConcurrentRessource;
using Threading::ConcurrentWriter;
using Threading::ConcurrentReader;
using Threading::getConcurrentWriter;
using Threading::getConcurrentReader;

namespace AI
{
    namespace Sensor
    {
        // SightSensor's implementation :

        const Sensor::SensorType SightSensor::Type = "SigthSensor";

        SightSensor::SightSensor(Ecs::Entity entity, int detectionRadius)
            : Sensor(Type, entity), detectionRadius_(detectionRadius)
        {
        }
        /**
         * Current implementation : check whether a other agent has entered the agent's detection area
         */
        std::vector<MemoryFact*> SightSensor::update(Ecs::World& world)
        {
            std::vector<MemoryFact*> newFacts;

            Ecs::ComponentGroup::ComponentTypeCollection types;
            types.insert(PositionComponent::Type);
            Ecs::ComponentGroup prototype(types);

	    // Get the position of the entity owning the sensor
	    Ecs::ComponentGroup sensorEntityComponents = world.getEntityComponents(entity_, prototype);
	    const Vec3Df& sensorEntityPosition =
	      getConcurrentReader<Ecs::Component, PositionComponent>(
								     sensorEntityComponents.getComponent(PositionComponent::Type)
								     )->getPosition();
            // Get all the entity with the component "position"
            Ecs::World::ComponentGroupCollection groupCollection = world.getComponents(prototype);
            Ecs::World::ComponentGroupCollection::iterator group;

            for(group = groupCollection.begin(); group != groupCollection.end(); ++group)
            {
                // Check if the entity can be detected by the sensor's owner
                const Ecs::Entity& entity = group->getEntity();
                if(entity != entity_)
                {
                    const Vec3Df& entityPosition =
                        getConcurrentReader<Ecs::Component, PositionComponent>(
                            group->getComponent(PositionComponent::Type)
                        )->getPosition();
		    float distance  = (sensorEntityPosition - entityPosition).getLength();
                    if(distance < detectionRadius_)
                    {
                        float belief = 1-distance/detectionRadius_;
                        newFacts.push_back(new SeeEntityFact(entity, entityPosition, belief));
                    }
                }
            }
            return newFacts;
        }

        // SeeEnnemyFact's implementation :
        const MemoryFact::MemoryFactType SeeEntityFact::Type = "sightFact";

        SeeEntityFact::SeeEntityFact(Ecs::Entity entity, const Geometry::Vec3Df& position, float belief):
            MemoryFact(Type, belief)
        {
            setCharacterId(entity);
            setPosition(position);
        }
    }
}
