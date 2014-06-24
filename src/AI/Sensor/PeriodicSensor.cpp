#include "PeriodicSensor.h"

namespace AI
{
    namespace Sensor
    {
        PeriodicSensor::PeriodicSensor(SensorType sensorType, Ecs::Entity entity, int updateRate)
            : Sensor(sensorType, entity), updateRate_(updateRate)
        {
        }

        PeriodicSensor::~PeriodicSensor()
        {
        }
     }
}
