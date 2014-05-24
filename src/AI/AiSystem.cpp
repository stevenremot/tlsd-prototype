#include "AiSystem.h"

#include "AiComponent.h"

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
                }
            }

        }
    }
}
