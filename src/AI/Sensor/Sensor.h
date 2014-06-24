#ifndef SENSOR_H
#define SENSOR_H

#include <string>

//#include "../MemoryFact.h"
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

            Sensor(SensorType sensorType, Ecs::Entity entity, Ecs::World& world, WorkingMemory& memory)
                : sensorType_(sensorType), entity_(entity), world_(world), memory_(memory){}
            virtual ~Sensor(){}
            virtual bool update() = 0;
            virtual void cleanMemory() = 0;

            bool hasBeenUpdated() const {return hasBeenUpdated_;}
            const SensorType& getSensorType() const {return sensorType_;}

        protected:
            SensorType sensorType_;
            Ecs::Entity entity_;
            Ecs::World& world_;
            WorkingMemory& memory_;
            bool hasBeenUpdated_;
        };
    }
}

#endif // SENSOR_H
