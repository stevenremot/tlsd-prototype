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
            PeriodicSensor(SensorType sensorType, Ecs::World& world, WorkingMemory& memory, int updateRate = 100);
            virtual ~PeriodicSensor();
        private:
            int updateRate_;
        };
    }
}

#endif // PERIODICSENSOR_H
