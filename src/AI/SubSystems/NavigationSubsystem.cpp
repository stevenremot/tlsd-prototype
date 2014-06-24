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

#include <typeinfo>

#include "../Action/MoveCloseToTargetAction.h"
#include "../Action/NoAction.h"
#include "TargetingComponent.h"
#include "../../Graph/PathFinding.h"

#include "../../Geometry/PositionComponent.h"
#include "../../Physics/MovementComponent.h"

using AI::Subsystem::Subsystem;

//using Geometry::Vec3Df;

namespace AI
{
    namespace Subsystem
    {
        const Subsystem::SubsystemType NavigationSubSystem::Type = "NavigationSubsystem";

        NavigationSubSystem::NavigationSubSystem(const NavMesh::NavMeshContainer& navMeshes)
            : Subsystem(Type),
              navMeshes_(navMeshes),
              isValid_(true)
        {
        }

        bool NavigationSubSystem::update(std::vector<Ecs::Component&>& components)
        {
            return false;
        }
        void NavigationSubSystem::executeAction(Action::Action* action, Ecs::ComponentGroup& components)
        {
            Action::MoveCloseToTargetAction* moveAction = dynamic_cast<Action::MoveCloseToTargetAction*>(action);
            if(moveAction == NULL)
                return;
            try
            {
                // Get all the needed components
                const Geometry::PositionComponent& positionComponent = static_cast<const Geometry::PositionComponent&>(components.getComponent(Geometry::PositionComponent::Type));
                const TargetingComponent& targetingComponent = static_cast<const TargetingComponent&>(components.getComponent(TargetingComponent::Type));
                Physics::MovementComponent& movementComponent = static_cast<Physics::MovementComponent&>(components.getComponent(Physics::MovementComponent::Type));

                if(!targetingComponent.hasValidTarget())
                    return;

                Geometry::Vec3Df navigationTarget = targetingComponent.getTargetPosition();
                const Geometry::Vec3Df& currentPosition = positionComponent.getPosition();
                // Compute the path to the target

                Graph::PlanarGraph::NodeCollection path;
                const NavMesh::NavMesh* currentNavMesh = NULL;
                Geometry::Vec2Df currentPosition2D = Geometry::Vec2Df(currentPosition.getX(), currentPosition.getY());
                Geometry::Vec2Df targetPosition2D = Geometry::Vec2Df(navigationTarget.getX(), navigationTarget.getY());
                if(navMeshes_.getNavMesh(currentPosition2D, currentNavMesh) && false)
                {

                    Graph::PlanarNode startNode;
                    Graph::PlanarNode endNode;
                    if(currentNavMesh->getNode(currentPosition2D, startNode)
                            && currentNavMesh->getNode(targetPosition2D, endNode))
                    {
                        // If a path exists add the current position of the cgaracter and its target position to the path
                        if(Graph::BasicAStar(currentNavMesh->getGraph(), startNode, endNode, path))
                        {
                            //path.insert(path.begin(), startNode);
                            path.push_back(targetPosition2D);
                        }
                    }
                }
                path.push_back(targetPosition2D);
                // Move the target
                float margin = 2.f;
                float maxSpeed = 1.0f;
                while(!path.empty() && targetingComponent.isTargetValid(navigationTarget))
                {
                    Geometry::Vec2Df currentTarget2D = path.front().getPosition();
                    Geometry::Vec3Df currentTarget = Geometry::Vec3Df(currentTarget2D.getX(), currentTarget2D.getY(), 0.0);
                    float distanceToNextTarget = (positionComponent.getPosition()- currentTarget).getLength();
                    // Wait until the character reach the target point
                    while(distanceToNextTarget > margin && targetingComponent.isTargetValid(navigationTarget))
                    {
                        distanceToNextTarget = (positionComponent.getPosition()- currentTarget).getLength();
                        const Geometry::Vec3Df& dir = currentTarget - positionComponent.getPosition();
                        Geometry::Vec3Df velocity = dir*(maxSpeed/distanceToNextTarget);
                        movementComponent.setVelocity(velocity);
                    }
                    if(!targetingComponent.isTargetValid(navigationTarget))
                        break;
                    movementComponent.setVelocity(Geometry::Vec3Df(0.f,0.f,0.f));
                    // Erase the point from the path
                    path.erase(path.begin());
                }
                movementComponent.setVelocity(Geometry::Vec3Df(0.f,0.f,0.f));
            }
            catch (const Ecs::ComponentGroup::UnexistingComponentException& e)
            {
                return;
            }
        }
    }
}
