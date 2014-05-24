#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "../AI/BasicAiModule.h"
#include "../AI/Blackboard.h"

namespace StateMachineTest
{
    const AI::BasicStateMachine::State Idle = "idle";
    const AI::BasicStateMachine::State CloseToTarget = "closeToTarget";
    const AI::BasicStateMachine::State OnAttack = "onAttack";

    float toIdleState(const AI::Blackboard&);
    float toOnAttack(const AI::Blackboard& blackboard);
    float toCloseToTarget(const AI::Blackboard& blackboard);

    void setupStateMachine(AI::BasicAiModule& aiModule);

    void testStateMachine();
}

#endif // STATEMACHINE_H
