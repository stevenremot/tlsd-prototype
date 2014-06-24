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

#ifndef AI_AICOMPONENT_H
#define AI_AICOMPONENT_H

//#include "Sensor/SensorComponent.h"
#include "SubSystems/TargetingComponent.h"
#include "SubSystems/SubsystemsManager.h"
#include "WorkingMemory.h"
#include "Blackboard.h"
//#include "Sensor/SensorManager.h"


#include "AiModule.h"


#include "../Ecs/Component.h"
#include "../Geometry/PositionComponent.h"
#include "../Physics/MovementComponent.h"


namespace AI
{
     /**
     * Component for all the NPC controlled by the computer
     */
    class AiComponent : public Ecs::Component
    {
    public:
        static const Ecs::Component::Type Type;

        AiComponent(Ecs::Entity entity, const NavMesh::NavMeshContainer& navMeshes)
            : Component(Type),
              entity_(entity),
              subsystemsManager_(entity, navMeshes),
              aiModule_(NULL) {}

        ~AiComponent();

        virtual const std::vector<Ecs::Component::Type>& getDependentComponents()
        {
            if(Dependencies.empty())
            {
                Dependencies.push_back(Geometry::PositionComponent::Type);
                Dependencies.push_back(Physics::MovementComponent::Type);
                Dependencies.push_back(Subsystem::TargetingComponent::Type);
            }
            return Dependencies;
        }

        void setAiModule(AiModule* aiModule) {aiModule_ = aiModule;}
        AiModule* getAiModule() {return aiModule_;}

        /*
        Blackboard& getBlackboard() {return blackboard_;}
        WorkingMemory& getMemory() {return memory_;}
        */

        Subsystem::SubSystemsManager& getSubsystemsManager()
        {
            return subsystemsManager_;
        }
        /*
        Sensor::SensorsManager& getSensorsManager()
        {
            return sensorsManager_;
        }
        */

    private:
        static std::vector<Ecs::Component::Type> Dependencies;

        const Ecs::Entity entity_;
        //WorkingMemory memory_;
        //Blackboard blackboard_;
        Subsystem::SubSystemsManager subsystemsManager_;
        //Sensor::SensorsManager sensorsManager_;
        AiModule* aiModule_;

    };
}
#endif // AI_AICOMPONENT_H
