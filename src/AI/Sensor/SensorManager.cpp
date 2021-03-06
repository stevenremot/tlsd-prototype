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

using namespace AI::Sensor;

namespace AI
{
    namespace Sensor
    {
        void SensorManager::addSensor(const Sensor::SensorType & sensorType)
        {
            vector< std::shared_ptr<Sensor> >::const_iterator sensor;
            for (sensor = sensorsList_.begin(); sensor != sensorsList_.end(); ++sensor)
            {
                if((*sensor)->getSensorType() == sensorType)
                    return;
            }
            if(sensorType == SightSensor::Type)
                sensorsList_.push_back(std::shared_ptr<Sensor>(new SightSensor(entity_)));
        }

        void SensorManager::removeSensor(const Sensor::SensorType &sensorType)
        {
            vector< std::shared_ptr<Sensor> >::iterator sensor;
            for (sensor = sensorsList_.begin(); sensor != sensorsList_.end(); ++sensor)
            {
                if((*sensor)->getSensorType() == sensorType)
                {
                    sensorsList_.erase(sensor);
                    return;
                }
            }
        }

        std::vector<MemoryFact*> SensorManager::updateSensors(Ecs::World& world)
        {
            std::vector<MemoryFact*> memoryFacts;
            vector< std::shared_ptr<Sensor> >::iterator sensor;
            for(sensor = sensorsList_.begin(); sensor != sensorsList_.end(); ++sensor)
            {
                std::vector<MemoryFact*> memoryFactsForSensor= (*sensor)->update(world);
                for(std::vector<MemoryFact*>::const_iterator it = memoryFactsForSensor.begin(); it != memoryFactsForSensor.end(); ++it)
                    memoryFacts.push_back(*it);
            }
            return memoryFacts;
        }
    }
}
