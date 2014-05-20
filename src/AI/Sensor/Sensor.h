#ifndef SENSOR_H
#define SENSOR_H

#include <string>

#include "../MemoryFact.h"
#include "../../Ecs/World.h"

using Ecs::World;

namespace AI
{

    /**
     * Base class for sensor
     * A sensor add memory's facts to the agent's memory.
     * It is responsible for cleaning the facts it has added.
     */
    class Sensor
    {
        typedef std::string SensorType;

    public:
        Sensor(SensorType sensorType, World& world, WorkingMemory& memory)
            : sensorType_(sensorType), world_(world), memory_(memory){}
        virtual ~Sensor(){}
        virtual bool update() = 0;
        virtual void cleanMemory() = 0;

        bool hasBeenUpdated() const {return hasBeenUpdated_;}
        const SensorType& getSensorType() const {return sensorType_;}

    protected:
        const SensorType sensorType_;
        World& world_;
        WorkingMemory& memory_;
        bool hasBeenUpdated_;
    };

}

#endif // SENSOR_H
