#include "SubsystemsManager.h"

#include "NavigationSubsystem.h"
#include "TargetingSubsystem.h"

using AI::Subsystem::NavigationSubSystem;
using AI::Subsystem::TargetingSubsystem;
using AI::Subsystem::Subsystem;


namespace AI
{
    namespace Subsystem
    {
        void SubSystemsManager::addSubsystem(const Subsystem::SubsystemType& type)
        {
            // TO DO : factory
            if(type == TargetingSubsystem::Type)
                subSystemsList_.push_back(new TargetingSubsystem(blackboard_, memory_));
            if(type == NavigationSubSystem::Type)
                subSystemsList_.push_back(new NavigationSubSystem(blackboard_));
        }

        void SubSystemsManager::updateSubsystems()
        {
            vector<Subsystem*>::iterator subsystem;
            for(subsystem = subSystemsList_.begin(); subsystem != subSystemsList_.end(); ++subsystem)
            {
                (*subsystem)->update();
            }
        }
    }

}
