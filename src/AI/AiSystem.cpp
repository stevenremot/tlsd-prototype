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
#include "../Threading/ConcurrentRessource.h"

using Threading::ConcurrentRessource;
using Threading::ConcurrentWriter;
using Threading::ConcurrentReader;
using Threading::getConcurrentWriter;
using Threading::getConcurrentReader;

namespace AI
{
    void AiSystem::run()
    {
        // Get all the entities which have an ai component

        Ecs::ComponentGroup::ComponentTypeCollection types;
        types.insert(AiComponent::Type);
        Ecs::ComponentGroup prototype(types);
        Ecs::World::ComponentGroupCollection groups = getWorld()->getComponents(prototype);

        // Update their positions
        Ecs::World::ComponentGroupCollection::iterator group;
        for (group = groups.begin(); group != groups.end(); ++group)
        {

            Ecs::ComponentGroup::ComponentTypeCollection types2;
            types2.insert(Subsystem::TargetingComponent::Type);
            types2.insert(Geometry::PositionComponent::Type);
            types2.insert(Physics::MovementComponent::Type);

            Ecs::ComponentGroup prototype2(types2);
            Ecs::ComponentGroup components = getWorld()->getEntityComponents((*group).getEntity(),prototype2);

            ConcurrentWriter<AiComponent> aiComponent =
                getConcurrentWriter<Ecs::Component, AiComponent>(
                    group->getComponent(AiComponent::Type)
                );

            // If the plan is over, compute a new one.
            AiModule* aiModule = aiComponent->getAiModule();
            Subsystem::SubSystemsManager& subsystemsManager = aiComponent->getSubsystemsManager();
            bool updateOver = subsystemsManager.updateSubsystems(components);
            if(updateOver)
            {
                /*
                if (currentAction != NULL)
                {
                        // Send the action to the relevant object
                    subsystemsManager.dispatchAction(currentAction, components);
                    if (currentAction->isFinished())
                    {
                        aiPlan->goToNextStep();
                        if (aiPlan->isPlanCompleted())
                            aiModule->computeNewPlan(components);
                    }
                }
                */
                // Get the actions sequence and dispatch them between subsystems
                Plan::AiPlan* aiPlan = aiModule->getPlan();
                if(aiPlan != NULL && !aiPlan->isPlanCompleted())
                {
                    aiPlan->goToNextStep();
                    Action::Action* currentAction = aiPlan->getCurrentAction();
                    if(currentAction!= NULL)
                        subsystemsManager.dispatchAction(currentAction, components);
                }
                if(aiPlan == NULL || aiPlan->isPlanCompleted())
                {
                    subsystemsManager.resetSubsystems();
                    aiModule->computeNewPlan(components);
                    if(aiModule->getPlan() != NULL)
                    {
                        Action::Action* currentAction = aiModule->getPlan()->getCurrentAction();
                        if(currentAction != NULL)
                            subsystemsManager.dispatchAction(currentAction, components);
                    }
                }
            }
        }
    }
}
