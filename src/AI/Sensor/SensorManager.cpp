#include "sensorsmanager.h"

#include "sightsensor.h"

namespace AI
{
    namespace Sensor
    {
        void SensorsManager::addSensor(const SensorType & sensorType)
        {
            vector<Sensor>::const_iterator sensor;
            for (sensor = sensorsList_.begin(); sensor != sensorsList_.end(); ++sensor)
            {
                if((*sensor)->getSensorType == sensorType)
                    return;
            }
            // TO DO : implement a factory instead
            if(sensorType == "sightSensor")
                sensorsList_.push_back(SightSensor(sensorType, world_, memory_));
        }

        void SensorsManager::removeSensor(const SensorType &sensorType)
        {
            vector<Sensor>::const_iterator sensor;
            for (sensor = sensorsList_.begin(); sensor != sensorsList_.end(); ++sensor)
            {
                if((*sensor)->getSensorType == sensorType)
                {
                    sensorsList_.erase(sensor);
                    return;
                }
            }
        }
    }
}
