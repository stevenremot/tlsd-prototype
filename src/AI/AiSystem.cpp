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

#include "AiSystem.h"

#include "AiComponent.h"
#include "../Threading/Thread.h"

namespace AI
{
    void AiSystem::run()
    {
        // Get all the entities which have an ai component
        Ecs::World world = getWorld();

        Ecs::ComponentGroup::ComponentTypeCollection types;
        types.insert(AiComponent::Type);
        Ecs::ComponentGroup prototype(types);
        Ecs::World::ComponentGroupCollection groups = world.getComponents(prototype);

        // Update their positions
        Ecs::World::ComponentGroupCollection::iterator group;
        for (group = groups.begin(); group != groups.end(); ++group)
        {
            AiComponent& aiComponent = static_cast<AiComponent &>(group->getComponent(AiComponent::Type));
            // update all the sensors
            Sensor::SensorsManager& sensorsManager = aiComponent.getSensorsManager();
            sensorsManager.updateSensors();
            // update the subsystems
            Subsystem::SubSystemsManager& subsystemsManager = aiComponent.getSubsystemsManager();
            subsystemsManager.updateSubsystems();

            // If the plan is over, compute a new one.
            AiModule* aiModule = aiComponent.getAiModule();
            aiModule->computeNewPlan();
            // Get the actions sequence and dispatch them between subsystems
            Plan::AiPlan* aiPlan = aiModule->getPlan();
            if(aiPlan != NULL)
            {
                while(!aiPlan->isPlanCompleted())
                {
                    Action::Action* currentAction = aiPlan->getCurrentAction();
                    // Send the action to the relevant object
                    subsystemsManager.dispatchAction(currentAction);
                    aiPlan->goToNextStep();
                    //Threading::sleep(0,50);
                }
            }

        }
    }
}
