#include "SubsystemsManager.h"

#include "NavigationSubsystem.h"

#include "../Action/MoveCloseToTargetAction.h"
#include "../Action/NoAction.h"

#include "../../Geometry/PositionComponent.h"
#include "../../Physics/MovementComponent.h"

#include "../../Ecs/World.h"

using std::vector;
using AI::Action::MoveCloseToTargetAction;
using Geometry::PositionComponent;
using Physics::MovementComponent;

namespace AI
{
    namespace Subsystem
    {
        SubSystemsManager::~SubSystemsManager()
        {
            while(!subSystemsList_.empty())
            {
                Subsystem* subSystem = subSystemsList_.back();
                if(NULL != subSystem)
                    delete subSystem;
                subSystemsList_.pop_back();
            }
        }

        void SubSystemsManager::addSubsystem( const Subsystem::SubsystemType& type)
        {
            if(type == NavigationSubSystem::Type)
            {
                subSystemsList_.push_back(new NavigationSubSystem());
            }
        }

        Subsystem* SubSystemsManager::getSubsystemByType(const Subsystem::SubsystemType& type)
        {
            vector<Subsystem*>::const_iterator it;
            for(it = subSystemsList_.begin(); it !=  subSystemsList_.end(); ++it)
                if(type == (*it)->getSubsystemType())
                    return (*it);
            return NULL;
        }

        bool SubSystemsManager::updateSubsystems(Ecs::ComponentGroup& components)
        {
            bool updateOver = true;
            vector<Subsystem*>::iterator subsystem;
            for(subsystem = subSystemsList_.begin(); subsystem != subSystemsList_.end(); ++subsystem)
            {
                updateOver = updateOver && (*subsystem)->update(components);
            }
            return updateOver;
        }

        void SubSystemsManager::dispatchAction(
            Action::Action* action,
            Ecs::ComponentGroup& components
        ) {
            Subsystem::SubsystemType subsystemType = "None";
            if(action->getType() == Action::MoveCloseToTargetAction::Type)
            {
                subsystemType = NavigationSubSystem::Type;
            }
            if(!(subsystemType == "None"))
                getSubsystemByType(subsystemType)->treatAction(action, components);
        }

        void SubSystemsManager::resetSubsystems()
        {
            std::vector<Subsystem*>::iterator subsystem;
            for ( subsystem = subSystemsList_.begin(); subsystem  != subSystemsList_.end(); ++subsystem)
                (*subsystem) -> reset();
        }

    }

}
