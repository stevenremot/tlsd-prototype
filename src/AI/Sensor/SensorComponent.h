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

#ifndef AI_SENSOR_SENSORCOMPONENT_H
#define AI_SENSOR_SENSORCOMPONENT_H

#include "SensorManager.h"
#include "../WorkingMemory.h"
#include "../AiComponent.h"
#include "../../Ecs/Component.h"

namespace AI
{
    namespace Sensor
    {
        class SensorComponent : public Ecs::Component
        {
        public:

            static const Ecs::Component::Type Type;

            SensorComponent(Ecs::Entity entity)
                : Ecs::Component(Type),
                  sensorsManager_(entity)
            {
            }

            virtual const std::vector<Ecs::Component::Type>& getDependentComponents()
            {
                if(Dependencies.empty())
                {
                    Dependencies.push_back(AI::AiComponent::Type);
                }
                return Dependencies;
            }

            SensorsManager& getSensorsManager() {return sensorsManager_;}

        private:
            static std::vector<Ecs::Component::Type> Dependencies;
            SensorsManager sensorsManager_;
        };
    }
}

#endif // AI_SENSOR_SENSORCOMPONENT_H
