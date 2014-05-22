#include "PeriodicSensor.h"

namespace AI
{
    namespace Sensor
    {
        PeriodicSensor::PeriodicSensor(SensorType sensorType, Ecs::World& world, WorkingMemory& memory,int updateRate)
            : Sensor(sensorType, world, memory), updateRate_(updateRate)
        {
        }

        PeriodicSensor::~PeriodicSensor()
        {
        }
     }
}
