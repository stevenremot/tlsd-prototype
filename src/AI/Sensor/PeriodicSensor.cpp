#include "periodicsensor.h"

namespace AI
{

    PeriodicSensor::PeriodicSensor(SensorType sensorType, Ecs::World& world, WorkingMemory& memory,int updateRate)
        : Sensor(sensorType, world, memory), updateRate_(updateRate)
    {
    }

    PeriodicSensor::~PeriodicSensor()
    {
    }

}
