#include "NavigationSubsystem.h"

#include "../Action/MoveCloseToTargetAction.h"

using AI::Subsystem::Subsystem;
using AI::Blackboard;

namespace AI
{
    namespace Subsystem
    {
        const Subsystem::SubsystemType NavigationSubSystem::Type = "NavigationSubsystem";

        NavigationSubSystem::NavigationSubSystem(Blackboard &blackboard) : Subsystem(Type, blackboard)
        {
        }

        bool NavigationSubSystem::update()
        {
            return false;
        }

        void NavigationSubSystem::updatePath()
        {
        }

        void NavigationSubSystem::executeAction(Action::Action *action)
        {
            Action::MoveCloseToTargetAction* moveAction =static_cast<Action::MoveCloseToTargetAction*>(action);
            navigationTarget_ = moveAction->getTargetPosition();
            // Compute the path to the target

            // Move the target
            while(!moveAction->isFinished())
            {
            }

        }
    }
}
