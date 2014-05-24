#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "../AI/BasicAiModule.h"

namespace StateMachineTest
{
    const AI::BasicStateMachine::State Idle = "idle";
    const AI::BasicStateMachine::State CloseToTarget = "closeToTarget";
    const AI::BasicStateMachine::State OnAttack = "onAttack";

    void setupStateMachine(AI::BasicStateMachine& stateMachine);

    void testStateMachine();
}

#endif // STATEMACHINE_H
