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

#ifndef AI_SENSOR_SIGHTSENSOR_H
#define AI_SENSOR_SIGHTSENSOR_H

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
        class SightSensor : public Sensor
        {
        public:

            static const Sensor::SensorType Type;

            SightSensor(Ecs::Entity entity, Ecs::World& world,WorkingMemory& memory, int detectionRadius = 100);

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

        class SeeEntityFact : public MemoryFact
        {
        public:
            static const MemoryFact::MemoryFactType Type;

            SeeEntityFact(Ecs::Entity entity, const Geometry::Vec3Df & position, float belief);
        };
    }
}

#endif // AI_SENSOR_SIGHTSENSOR_H
