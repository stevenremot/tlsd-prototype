#include "stateMachine.h"

#include "../Ecs/World.h"
#include "../AI/AiComponent.h"
#include "../AI/BasicAiModule.h"
#include "../AI/Action/MoveCloseToTargetAction.h"
#include "../AI/Action/NoAction.h"

using AI::BasicStateMachine;
using AI::BasicAiModule;
using AI::Action::MoveCloseToTargetAction;

using namespace AI;

namespace StateMachineTest
{

    float toIdleState(const AI::Blackboard&)
    {
        return 0.1f;
    }

    float toOnAttack(const Blackboard& blackboard)
    {
        /*
        Ecs::Entity targetEntity = blackboard.getTargetId();
        Ecs::World w = Ecs::World();
        w.getEntityComponents(targetEntity,)
        */
        float maxDistance = 10.f;
        if((blackboard.getNavigationTarget()-blackboard.getCurrentPosition()).getLength() < maxDistance)
        {
            return 1.0f;
        }
        return 0.f;
    }

    float toCloseToTarget(const Blackboard& blackboard)
    {
        float maxDistance = 80.f;
        if((blackboard.getNavigationTarget()-blackboard.getCurrentPosition()).getLength() < maxDistance)
        {
            return 1.0f;
        }
        return 0.f;
    }

    void setupStateMachine(BasicAiModule& aiModule)
    {
        aiModule.addState(CloseToTarget);
        aiModule.addState(OnAttack);

        //Transition Idle -> CloseToTarget
        BasicAiModule::Transition idleToCloseToTarget(Action::MoveCloseToTargetAction::Type, &toCloseToTarget);
        aiModule.addTransition(Idle, CloseToTarget, idleToCloseToTarget);

        // Transition CloseToTarget- > OnAttack
        BasicAiModule::Transition closeToTargetToOnAttack(AI::Action::MoveCloseToTargetAction::Type, &toOnAttack);
        aiModule.addTransition(CloseToTarget, OnAttack, closeToTargetToOnAttack);
        // Transition OnAttack- > Idle
        BasicAiModule::Transition onAttackToIdle(AI::Action::NoAction::Type, &toIdleState);
        aiModule.addTransition(OnAttack, Idle, onAttackToIdle);

        // Transition CloseToTarget- > Idle
        BasicAiModule::Transition closeToTargetToIdle(AI::Action::NoAction::Type, &toIdleState);
        aiModule.addTransition(CloseToTarget, Idle, closeToTargetToIdle);
    }

    void testStateMachine()
    {
        Ecs::World w = Ecs::World();
        // Create the unit with the ai module
        Ecs::Entity e1 = w.createEntity();
        AiComponent* aiComponent = new AiComponent(w);
        w.addComponent(e1, aiComponent);

        BasicAiModule* aiModule = new BasicAiModule(aiComponent->getBlackboard(), Idle);
        //BasicStateMachine& stateMachine = aiModule->getStateMachine();
        setupStateMachine(*aiModule);
        aiComponent->setAiModule(aiModule);

        aiComponent->getBlackboard().setNavigationTarget(Geometry::Vec3Df(70.0,0.f,0.f));

        aiModule->computeNewPlan();
        aiModule->computeNewPlan();
        aiModule->computeNewPlan();

        int k = 0;

        // Add a sight sensor
        //AI::Sensor::SensorsManager& sensorsManager = aiComponent->getSensorsManager();
        //sensorsManager.addSensor(AI::Sensor::SightSensor::Type);
    }
}
