#include "NavigationSubsystem.h"

#include "../Action/MoveCloseToTargetAction.h"

using AI::Subsystem::Subsystem;
using AI::Blackboard;

using Geometry::Vec3Df;

namespace AI
{
    namespace Subsystem
    {
        const Subsystem::SubsystemType NavigationSubSystem::Type = "NavigationSubsystem";

        NavigationSubSystem::NavigationSubSystem(Blackboard &blackboard,
                                                 Geometry::PositionComponent &positionComponent,
                                                 Physics::MovementComponent& movementComponent)
            : Subsystem(Type, blackboard),
              positionComponent_(positionComponent),
              movementComponent_(movementComponent)
        {
        }

        bool NavigationSubSystem::update()
        {
            return false;
        }
        void NavigationSubSystem::executeAction(Action::Action *action)
        {
            Action::MoveCloseToTargetAction* moveAction =static_cast<Action::MoveCloseToTargetAction*>(action);
            navigationTarget_ = moveAction->getTargetPosition();
            // Compute the path to the target

            // Move the target
            float margin = 10.f;
            float maxSpeed = 5;
            while(!moveAction->isFinished())
            {
                float distanceToTarget = (positionComponent_.getPosition()- navigationTarget_).getLength();
                if( distanceToTarget < margin)
                {
                    moveAction->setFinished(true);
                    movementComponent_.setVelocity(Vec3Df(0.f,0.f,0.f));
                }
                else
                {
                    const Geometry::Vec3Df& test = navigationTarget_ - positionComponent_.getPosition();
                    Geometry::Vec3Df velocity = test*(maxSpeed/distanceToTarget);
                    movementComponent_.setVelocity(velocity);
                }
            }

        }
    }
}
