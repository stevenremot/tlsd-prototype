#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "../AI/BasicAiModule.h"
#include "../AI/Blackboard.h"

namespace StateMachineTest
{
    const AI::BasicStateMachine::State Idle = "idle";
    const AI::BasicStateMachine::State CloseToTarget = "closeToTarget";
    const AI::BasicStateMachine::State OnAttack = "onAttack";

    float toIdleState(const Ecs::ComponentGroup&);
    float toOnAttack(const Ecs::ComponentGroup& components);
    float toCloseToTarget(const Ecs::ComponentGroup& components);

    void setupStateMachine(AI::BasicAiModule& aiModule);

    void testStateMachine();
}

#endif // STATEMACHINE_H
