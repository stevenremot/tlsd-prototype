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

            Subsystem::SubSystemsManager& subsystemsManager = aiComponent.getSubsystemsManager();

            Ecs::ComponentGroup::ComponentTypeCollection types2;
            types2.insert(Subsystem::TargetingComponent::Type);
            types2.insert(Geometry::PositionComponent::Type);
            types2.insert(Physics::MovementComponent::Type);

            Ecs::ComponentGroup prototype2(types2);
            Ecs::ComponentGroup components = world.getEntityComponents((*group).getEntity(),prototype2);

            // If the plan is over, compute a new one.
            AiModule* aiModule = aiComponent.getAiModule();
            // Get the actions sequence and dispatch them between subsystems
            Plan::AiPlan* aiPlan = aiModule->getPlan();
            if(aiPlan != NULL && !aiPlan->isPlanCompleted())
            {
                Action::Action* currentAction = aiPlan->getCurrentAction();
                // Send the action to the relevant object
                subsystemsManager.dispatchAction(currentAction, components);
                aiPlan->goToNextStep();
            }
            else
            {
                aiModule->computeNewPlan(components);
            }

        }
    }
}
