#ifndef SENSORSMANAGER_H
#define SENSORSMANAGER_H

#include <vector>

#include "Sensor.h"
#include "../../Ecs/World.h"

using std::vector;

namespace AI
{
    namespace Sensor
    {
        /**
         * Add, remove or update (?) the sensors
         * Run it in a thread and sequentially update all sensors or run all sensors in different threads ?
         */
        class SensorsManager
        {
        public:
            SensorsManager(Ecs::Entity entity, Ecs::World & world, WorkingMemory& memory)
                : entity_(entity), world_(world), memory_(memory){}

            /**
             * Add a new sensor. If the sensor is already in the list, it's not added.
             */
            void addSensor(const AI::Sensor::Sensor::SensorType & sensorType);

            /**
             * Remove a sensor. If the sensor's type does not match a type in the sensors list, no component is removed.
             */
            void removeSensor(const AI::Sensor::Sensor::SensorType & sensorType);

            void updateSensors();

        private:
            typedef vector<Sensor*> SensorsList;

            const Ecs::Entity entity_;
            Ecs::World& world_;
            SensorsList sensorsList_;
            WorkingMemory& memory_;
        };
    }
}

#endif // SENSORSMANAGER_H
