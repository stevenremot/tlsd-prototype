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
            // TO DO : implement a factory instead
            //if(sensorType == "sightSensor")
            if(sensorType == SightSensor::Type)
                sensorsList_.push_back(new SightSensor(world_, memory_));
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

        void SensorsManager::updateSensors()
        {
            vector<Sensor*>::iterator sensor;
            for(sensor = sensorsList_.begin(); sensor != sensorsList_.end(); ++sensor)
            {
                (*sensor)->update();
            }
        }
    }
}
