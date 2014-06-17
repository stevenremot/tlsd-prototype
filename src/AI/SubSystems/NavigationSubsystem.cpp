/*
   This file is part of The Lost Souls Downfall prototype.

    The Lost Souls Downfall prototype is free software: you can
    redistribute it and/or modify it under the terms of the GNU
    General Public License as published by the Free Software
    Foundation, either version 3 of the License, or (at your option)
    any later version.

    The Lost Souls Downfall prototype is distributed in the hope that
    it will be useful, but WITHOUT ANY WARRANTY; without even the
    implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
    PURPOSE.  See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with The Lost Souls Downfall prototype.  If not, see
    <http://www.gnu.org/licenses/>.
*/

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
