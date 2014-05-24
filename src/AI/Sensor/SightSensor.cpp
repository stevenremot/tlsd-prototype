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

namespace AI
{
    namespace Sensor
    {
        // SightSensor's implementation :

        const Sensor::SensorType SightSensor::Type = "SigthSensor";

        SightSensor::SightSensor(Ecs::World& world, WorkingMemory&memory, int updateRate, int detectionRadius)
            : PeriodicSensor(Type, world, memory, updateRate), detectionRadius_(detectionRadius)
        {
        }
        /**
         * Current implementation : check whether a other agent has entered the agent's detection area
         */
        bool SightSensor::update()
        {
            // Get all the memory facts of type "sight fact" already registered in memory
            vector<MemoryFact*> sightFacts;
            memory_.getMemoryFactsByType("sightFact", sightFacts);

            // Get all the entity with the component "position"
            Ecs::ComponentGroup::ComponentTypeCollection types;
            types.insert(PositionComponent::Type);
            types.insert(MovementComponent::Type);
            Ecs::ComponentGroup prototype(types);
            //world_.getEntityComponents(1,prototype);
            Ecs::World::ComponentGroupCollection groupCollection = world_.getComponents(prototype);
            Ecs::World::ComponentGroupCollection::iterator group;

            for(group = groupCollection.begin(); group != groupCollection.end(); ++group)
            {
                // Check if the entity can be detected by the sensor's owner
                const Ecs::Entity & entity = group->getEntity();
                const Vec3Df & entityPosition = static_cast<PositionComponent &>(group->getComponent(PositionComponent::Type)).getPosition();
                // Check if the entity is already in the memory of the sensor's owner
                MemoryFact* oldFactForEntity = NULL;
                for(unsigned int i =0; i < sightFacts.size(); i++)
                {
                    if(sightFacts[i]->getCharacterId() == entity)
                    {
                        oldFactForEntity = sightFacts[i];
                        break;
                    }
                }
                if(entityPosition.getSquaredLength() < detectionRadius_*detectionRadius_)
                {
                    // Check if the entity is already in the memory
                    // If so, update the fact. Otherwise, add a new fact
                    float belief = max(1-entityPosition.getLength()/detectionRadius_,0.f);
                    if(oldFactForEntity != NULL)
                    {
                        oldFactForEntity->setPosition(entityPosition);
                        oldFactForEntity->setFactBelief(belief);
                    }
                    else
                    {
                        memory_.addMemoryFact(new SeeEntityFact(entity, entityPosition, belief));
                    }
                }
                else if(oldFactForEntity != NULL)
                {
                    memory_.removeMemoryFact(oldFactForEntity);
                }
            }
            return false;
        }

        // SeeEnnemyFact's implementation :
        const MemoryFact::MemoryFactType SeeEntityFact::Type = "sightFact";

        SeeEntityFact::SeeEntityFact(Ecs::Entity entity, const Geometry::Vec3Df & position, float belief):
            MemoryFact(Type, belief)
        {
            setCharacterId(entity);
            setPosition(position);
        }
    }
}