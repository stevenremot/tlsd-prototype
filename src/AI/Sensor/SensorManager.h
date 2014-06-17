/*
   This file is part of The Lost Souls Downfall prototype.

    The Lost Souls Downfall prototype is free software: you can
    redistribute it and/or modify it under the terms of the GNU
    General Public License as published by the Free Software
    Foundation, either version 3 of the License, or (at your option)
    any later version.

    The Lost Souls Downfall prototype is distributed in the hope that
    it will be useful, but WITHOUT ANY WARRANTY; without even the
    implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
    PURPOSE.  See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with The Lost Souls Downfall prototype.  If not, see
    <http://www.gnu.org/licenses/>.
*/

#ifndef AI_SENSOR_SENSORSMANAGER_H
#define AI_SENSOR_SENSORSMANAGER_H

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

#endif // AI_SENSOR_SENSORSMANAGER_H