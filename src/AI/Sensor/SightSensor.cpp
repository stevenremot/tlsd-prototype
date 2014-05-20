#include "SightSensor.h"

#include "../../Ecs/ComponentGroup.h"
#include "../../PositionComponent.h"

using std::max;

namespace AI
{
    namespace Sensor
    {
        SightSensor::SightSensor(Ecs::World& world, WorkingMemory&memory, int updateRate, int detectionRadius)
            : PeriodicSensor("sightSensor", world, memory, updateRate), detectionRadius_(detectionRadius)
        {
        }
        /**
         * Current implementation : check whether a other agent has entered the agent's detection area
         */
        bool SightSensor::update()
        {
            // Get all the entity with the component "position"
            Ecs::ComponentGroup::ComponentTypeCollection types;
            types.insert(PositionComponent::Type);
            Ecs::ComponentGroup prototype(types);

            Ecs::ComponentGroup::ComponentCollection groupCollection = world_.getComponents(prototype);
            Ecs::ComponentGroup::ComponentCollection::const_iterator group;

            for(group = groupCollection.begin(); group != groupCollection.end(); ++group)
            {
                // Check if the entity can be detected by the sensor's owner
                const Ecs::Entity & entity = (*group)->getEntity();
                const Geometry::Vec3Df & position = static_cast<PositionComponent &>((*group)->getComponent(PositionComponent::Type)).getPosition();
                if(position.getSquaredLength() < detectionRadius_*detectionRadius_)
                {
		  // TO DO : Check if the entity is already in the memory
		  // If so, update the fact
		 
		  MemoryFact * fact =  new MemoryFact("sightFact", belief);
		  float belief = max(1-entityPosition.getLength()/detectionRadius_,0);
		  fact->setCharacterId(entity);
		  fact->setPosition(position);
		  memory_.addMemoryFact(fact);
                }
            }
    }
}
