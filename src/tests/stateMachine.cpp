#include "stateMachine.h"

#include "../Ecs/World.h"
#include "../AI/AiComponent.h"
#include "../AI/BasicAiModule.h"

using AI::BasicStateMachine;
using AI::BasicAiModule;

namespace StateMachineTest
{
    void setupStateMachine(AI::BasicStateMachine& stateMachine)
    {
        stateMachine.addState(CloseToTarget);
        stateMachine.addState(OnAttack);

        stateMachine.addTransition(Idle, CloseToTarget, &BasicStateMachine::f);
        stateMachine.addTransition(CloseToTarget, OnAttack, &BasicStateMachine::f);
        stateMachine.addTransition(OnAttack, Idle, &BasicStateMachine::f);
    }

    void testStateMachine()
    {
        Ecs::World w = Ecs::World();
        // Create the unit with the ai module
        Ecs::Entity e1 = w.createEntity();
        AI::AiComponent* aiComponent = new AI::AiComponent(w);
        w.addComponent(e1, aiComponent);

        AI::BasicAiModule* aiModule = new AI::BasicAiModule(aiComponent->getBlackboard(), Idle);
        BasicStateMachine& stateMachine = aiModule->getStateMachine();
        setupStateMachine(stateMachine);
        aiComponent->setAiModule(aiModule);

        aiModule->computeNewPlan();
        aiModule->computeNewPlan();
        aiModule->computeNewPlan();

        // Add a sight sensor
        //AI::Sensor::SensorsManager& sensorsManager = aiComponent->getSensorsManager();
        //sensorsManager.addSensor(AI::Sensor::SightSensor::Type);
    }
}
