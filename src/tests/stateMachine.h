#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "../AI/BasicAiModule.h"
#include "../AI/Blackboard.h"

namespace StateMachineTest
{
    const AI::BasicStateMachine::State Idle = "idle";
    const AI::BasicStateMachine::State CloseToTarget = "closeToTarget";
    const AI::BasicStateMachine::State OnAttack = "onAttack";

    float toIdleState(Ecs::ComponentGroup&, const AI::Blackboard&);
    float toOnAttack(Ecs::ComponentGroup& components, const AI::Blackboard& blackboard);
    float toCloseToTarget(Ecs::ComponentGroup& components, const AI::Blackboard& blackboard);

    void setupStateMachine(AI::BasicAiModule& aiModule);

    void testStateMachine();
}

#endif // STATEMACHINE_H
