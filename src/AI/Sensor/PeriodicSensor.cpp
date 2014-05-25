#include "PeriodicSensor.h"

namespace AI
{
    namespace Sensor
    {
        PeriodicSensor::PeriodicSensor(SensorType sensorType, Ecs::Entity entity, Ecs::World& world, WorkingMemory& memory,int updateRate)
            : Sensor(sensorType, entity, world, memory), updateRate_(updateRate)
        {
        }

        PeriodicSensor::~PeriodicSensor()
        {
        }
     }
}
