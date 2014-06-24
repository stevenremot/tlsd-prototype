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

#ifndef AI_SENSOR_SENSOR_H
#define AI_SENSOR_SENSOR_H

#include <string>

#include "../WorkingMemory.h"
#include "../../Ecs/World.h"

namespace AI
{
    namespace Sensor
    {
        /**
         * Base class for sensor
         * A sensor add memory's facts to the agent's memory.
         * It is responsible for cleaning the facts it has added.
         */
        class Sensor
        {
        public:
            typedef std::string SensorType;

            Sensor(SensorType sensorType, Ecs::Entity entity)
                : sensorType_(sensorType), entity_(entity){}
            virtual ~Sensor(){}
            virtual std::vector<MemoryFact*> update(Ecs::World& world) = 0;
            virtual void cleanMemory() = 0;

            bool hasBeenUpdated() const {return hasBeenUpdated_;}
            const SensorType& getSensorType() const {return sensorType_;}

        protected:
            SensorType sensorType_;
            Ecs::Entity entity_;
            bool hasBeenUpdated_;
        };
    }
}

#endif // AI_SENSOR_SENSOR_H
