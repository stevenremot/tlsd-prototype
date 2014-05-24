#include "SubsystemsManager.h"

#include "NavigationSubsystem.h"
#include "TargetingSubsystem.h"

#include "../Action/MoveCloseToTargetAction.h"
#include "../Action/NoAction.h"


using std::vector;
using AI::Action::MoveCloseToTargetAction;

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

        Subsystem* SubSystemsManager::getSubsystemByType(const Subsystem::SubsystemType& type)
        {
            vector<Subsystem*>::const_iterator it;
            for(it = subSystemsList_.begin(); it !=  subSystemsList_.end(); ++it)
                if(type == (*it)->getSubsystemType())
                    return (*it);
            return NULL;
        }

        void SubSystemsManager::updateSubsystems()
        {
            vector<Subsystem*>::iterator subsystem;
            for(subsystem = subSystemsList_.begin(); subsystem != subSystemsList_.end(); ++subsystem)
            {
                (*subsystem)->update();
            }
        }

        void SubSystemsManager::dispatchAction(Action::Action* action)
        {
            if(action == NULL)
                return;
            Subsystem::SubsystemType subsystemType;
            if(action->getType() == Action::MoveCloseToTargetAction::Type)
            {
                subsystemType = NavigationSubSystem::Type;
            }
        }
    }

}
