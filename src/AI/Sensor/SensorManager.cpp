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

#include "SensorManager.h"

#include "SightSensor.h"

//using AI::Sensor::Sensor::SensorType;
//using AI::Sensor::Sensor;

using namespace AI::Sensor;

namespace AI
{
    namespace Sensor
    {
        void SensorsManager::addSensor(const Sensor::SensorType & sensorType)
        {
            vector<Sensor*>::const_iterator sensor;
            for (sensor = sensorsList_.begin(); sensor != sensorsList_.end(); ++sensor)
            {
                if((*sensor)->getSensorType() == sensorType)
                    return;
            }
            //if(sensorType == "sightSensor")
            if(sensorType == SightSensor::Type)
                sensorsList_.push_back(new SightSensor(entity_));
        }

        void SensorsManager::removeSensor(const Sensor::SensorType &sensorType)
        {
            vector<Sensor*>::iterator sensor;
            for (sensor = sensorsList_.begin(); sensor != sensorsList_.end(); ++sensor)
            {
                if((*sensor)->getSensorType() == sensorType)
                {
                    sensorsList_.erase(sensor);
                    return;
                }
            }
        }

        void SensorsManager::updateSensors(Ecs::World& world, WorkingMemory& memory)
        {
            vector<Sensor*>::iterator sensor;
            for(sensor = sensorsList_.begin(); sensor != sensorsList_.end(); ++sensor)
            {
                (*sensor)->update(world, memory);
            }
        }
    }
}
