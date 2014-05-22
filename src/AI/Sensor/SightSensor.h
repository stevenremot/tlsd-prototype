#ifndef SIGHTSENSOR_H
#define SIGHTSENSOR_H

#include "PeriodicSensor.h"
#include "../../Ecs/Entity.h"
#include "../../Geometry/Vec3D.h"


namespace AI
{
    namespace Sensor
    {
        /**
         * Sensor checking whether the agent can see others agents.
         */
        class SightSensor : public PeriodicSensor
        {
        public:

            static const Sensor::SensorType Type;

            SightSensor(Ecs::World& world,WorkingMemory& memory, int updateRate = 100, int detectionRadius = 100);

            /**
             * Check if a  ententy entered the detection area of the current entity
             * TO DO : implement field of view
             */
            virtual bool update();
            /**
             * TO DO
             */
            void cleanMemory(){}
        private:

            float detectionRadius_;
        };
    }
}

#endif // SIGHTSENSOR_H
