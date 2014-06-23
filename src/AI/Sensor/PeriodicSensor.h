#ifndef PERIODICSENSOR_H
#define PERIODICSENSOR_H

#include "Sensor.h"

namespace AI
{
    namespace Sensor
    {
        /**
         * Base class for sensor which are periodically updated
         */
        class PeriodicSensor : public Sensor
        {
        public:
            PeriodicSensor(SensorType sensorType, Ecs::Entity entity, Ecs::World& world, WorkingMemory& memory);
            virtual ~PeriodicSensor();
        private:
        };
    }
}

#endif // PERIODICSENSOR_H
