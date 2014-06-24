#include "SubsystemsManager.h"

#include "NavigationSubsystem.h"
#include "TargetingSubsystem.h"

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

        void SubSystemsManager::addSubsystem(const Subsystem::SubsystemType& type, Ecs::World& world)
        {
            if(type == NavigationSubSystem::Type)
            {
                // Get the movement and position components.
                // If they do not exist, don't add the navigation subsystem
                // TODO : Launch an exception ?
                /*
                Ecs::ComponentGroup::ComponentTypeCollection types;
                types.insert(PositionComponent::Type);
                types.insert(MovementComponent::Type);
                Ecs::ComponentGroup prototype(types);
                Ecs::ComponentGroup components = world.getEntityComponents(entity_, prototype);
                Geometry::PositionComponent& positionComponent = static_cast<Geometry::PositionComponent&>(components.getComponent(PositionComponent::Type));
                Physics::MovementComponent& movementComponent = static_cast<Physics::MovementComponent&>(components.getComponent(MovementComponent::Type));
                */
                subSystemsList_.push_back(new NavigationSubSystem(navMeshes_));
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

        void SubSystemsManager::updateSubsystems(std::vector<Ecs::Component&>& components)
        {
            vector<Subsystem*>::iterator subsystem;
            for(subsystem = subSystemsList_.begin(); subsystem != subSystemsList_.end(); ++subsystem)
            {
                (*subsystem)->update(components);
            }
        }

        void SubSystemsManager::dispatchAction(Action::Action* action, Ecs::ComponentGroup& components)
        {
            Subsystem::SubsystemType subsystemType = "None";
            if(action->getType() == Action::MoveCloseToTargetAction::Type)
            {
                subsystemType = NavigationSubSystem::Type;
            }
            if(!(subsystemType == "None"))
                getSubsystemByType(subsystemType)->executeAction(action, components);
        }
    }

}
