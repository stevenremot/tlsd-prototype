#include "stateMachine.h"

#include <vector>

#include "../Ecs/World.h"
#include "../AI/AiComponent.h"
#include "../AI/BasicAiModule.h"
#include "../AI/Action/MoveCloseToTargetAction.h"
#include "../AI/Action/NoAction.h"
#include "../AI/SubSystems/NavigationSubsystem.h"
#include "../AI/SubSystems/TargetingSubsystem.h"
#include "../AI/Sensor/SightSensor.h"
#include "../AI/AiSystem.h"
#include "../AI/NavMesh/NavMeshContainer.h"

#include "../Geometry/PositionComponent.h"
#include "../Physics/MovementComponent.h"
#include "../Physics/MovementSystem.h"

#include "../Threading/Thread.h"

using AI::BasicStateMachine;
using AI::BasicAiModule;
using AI::Action::MoveCloseToTargetAction;

using namespace AI;

using std::vector;

namespace StateMachineTest
{

    float toIdleState(Ecs::ComponentGroup& , const AI::Blackboard&)
    {
        return 0.1f;
    }

    float toOnAttack(Ecs::ComponentGroup& components, const Blackboard& blackboard)
    {
        Geometry::PositionComponent& positionComponent = static_cast<Geometry::PositionComponent&>(components.getComponent(Geometry::PositionComponent::Type));
        float maxDistance = 10.f;
        if((blackboard.getNavigationTarget()-positionComponent.getPosition()).getLength() < maxDistance)
        {
            return 1.0f;
        }
        return 0.f;
    }

    float toCloseToTarget(Ecs::ComponentGroup& components, const Blackboard& blackboard)
    {
        Geometry::PositionComponent& positionComponent = static_cast<Geometry::PositionComponent&>(components.getComponent(Geometry::PositionComponent::Type));
        float maxDistance = 120.f;
        if((blackboard.getNavigationTarget()-positionComponent.getPosition()).getLength() < maxDistance)
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
        NavMesh::NavMeshContainer navMeshes;

        Ecs::Entity e1 = w.createEntity();
        // Create component for e1
        Geometry::PositionComponent* positionComponentE1 = new Geometry::PositionComponent(Geometry::Vec3Df(0.f,0.f,0.0f));
        Physics::MovementComponent* movementComponentE1= new Physics::MovementComponent(Geometry::Vec3Df(0.f,0.f,0.0f));
        w.addComponent(e1, positionComponentE1);
        w.addComponent(e1, movementComponentE1);

        Ecs::ComponentGroup::ComponentTypeCollection types;
        types.insert(Physics::MovementComponent::Type);
        types.insert(Geometry::PositionComponent::Type);

        Ecs::ComponentGroup prototype(types);
        Ecs::ComponentGroup components = w.getEntityComponents(e1, prototype);
        AI::AiComponent* aiComponent = new AI::AiComponent(e1,w, navMeshes);
        BasicAiModule* aiModule = new BasicAiModule(components, aiComponent->getBlackboard(), Idle);
        setupStateMachine(*aiModule);
        aiComponent->setAiModule(aiModule);
        w.addComponent(e1, aiComponent);

        // Add a sight sensor
        AI::Sensor::SensorsManager& sensorsManager = aiComponent->getSensorsManager();
        sensorsManager.addSensor(AI::Sensor::SightSensor::Type);

        // Add navigation and targeting subsytems
        AI::Subsystem::SubSystemsManager& subsystemsManager = aiComponent->getSubsystemsManager();
        subsystemsManager.addSubsystem(AI::Subsystem::TargetingSubsystem::Type);
        subsystemsManager.addSubsystem(AI::Subsystem::NavigationSubSystem::Type);

        // Create an other entity
        Ecs::Entity e2 = w.createEntity();
        Geometry::PositionComponent* positionComponent = new Geometry::PositionComponent(Geometry::Vec3Df(0.f,80.f,0.0f));
        w.addComponent(e2, positionComponent);
        w.addComponent(e2, new Physics::MovementComponent(Geometry::Vec3Df(0.f,0.f,0.0f)));

        // Create the systems for ai and movement
        AI::AiSystem aiSystem(w);
        Physics::MovementSystem movementSystem(w);

        vector<Threading::ThreadableInterface*> aiSystemVector;
        vector<Threading::ThreadableInterface*> movementSystemVector;
        aiSystemVector.push_back(&aiSystem);
        movementSystemVector.push_back(&movementSystem);

        Threading::Thread aiThread(aiSystemVector, 5);
        Threading::Thread movementThread(movementSystemVector, 5);

        aiThread.start();
        movementThread.start();
        bool b = true;
        while(b)
        {
            if((positionComponentE1->getPosition()-positionComponent->getPosition()).getLength() < 10.f)
                b = false;
        }

        aiThread.stop();
        movementThread.stop();
        aiModule->computeNewPlan();
    }
}
