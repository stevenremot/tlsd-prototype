#include "NavigationSubsystem.h"

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
    }
}
