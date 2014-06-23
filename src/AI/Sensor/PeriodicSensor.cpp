#include "PeriodicSensor.h"

namespace AI
{
    namespace Sensor
    {
        PeriodicSensor::PeriodicSensor(SensorType sensorType, Ecs::Entity entity, Ecs::World& world, WorkingMemory& memory)
            : Sensor(sensorType, entity, world, memory)
        {
        }

        PeriodicSensor::~PeriodicSensor()
        {
        }
     }
}
