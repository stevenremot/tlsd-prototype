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
#include <cfloat>

#include "../Action/MoveCloseToTargetAction.h"
#include "TargetingComponent.h"
#include "../../Graph/PathFinding.h"

#include "../../Geometry/PositionComponent.h"
#include "../../Physics/MovementComponent.h"

using AI::Subsystem::Subsystem;

using Threading::ConcurrentRessource;
using Threading::ConcurrentReader;
using Threading::ConcurrentWriter;
using Threading::getConcurrentReader;
using Threading::getConcurrentWriter;

//using Geometry::Vec3Df;

namespace AI
{
    namespace Subsystem
    {
        const Subsystem::SubsystemType NavigationSubSystem::Type = "NavigationSubsystem";

        NavigationSubSystem::NavigationSubSystem()
            : Subsystem(Type)
        {}

        bool NavigationSubSystem::update(Ecs::ComponentGroup& components)
        {
            if(getCurrentAction()->getType() != Action::MoveCloseToTargetAction::Type)
            {
                currentPath_.clear();
                ConcurrentWriter<Physics::MovementComponent> movementComponent =
                    getConcurrentWriter<Ecs::Component, Physics::MovementComponent>(
                        components.getComponent(Physics::MovementComponent::Type)
                    );
                movementComponent->setVelocity(Geometry::Vec3Df(0.0, 0.0, 0.0));
                return true;
            }
            try
            {
                // Get all the needed components
                ConcurrentReader<Geometry::PositionComponent> positionComponent =
                    getConcurrentReader<Ecs::Component, Geometry::PositionComponent>(
                        components.getComponent(Geometry::PositionComponent::Type)
                    );
                ConcurrentReader<TargetingComponent> targetingComponent =
                    getConcurrentReader<Ecs::Component, TargetingComponent>(
                        components.getComponent(TargetingComponent::Type)
                    );
                ConcurrentWriter<Physics::MovementComponent> movementComponent =
                    getConcurrentWriter<Ecs::Component, Physics::MovementComponent>(
                        components.getComponent(Physics::MovementComponent::Type)
                    );

                if(!currentPath_.empty())
                {

                    const Geometry::Vec3Df& currentTarget = (*currentPath_.begin());
                    const Geometry::Vec3Df& finalTarget = currentPath_.back();
                    if(targetingComponent->isTargetValid(finalTarget))
                    {
                        float margin = 2.f;
                        float maxSpeed = 0.2f;//0.5f;
                        float distanceToNextTarget = (positionComponent->getPosition()- currentTarget).getLength();
                        if(distanceToNextTarget > margin)
                        {
                            const Geometry::Vec3Df& dir = currentTarget - positionComponent->getPosition();
                            Geometry::Vec3Df velocity = dir*(maxSpeed/(distanceToNextTarget + FLT_EPSILON)); // avoid division by 0 ?
                            movementComponent->setVelocity(velocity);
                        }
                        else
                        {
                            movementComponent->setVelocity(Geometry::Vec3Df(0.0, 0.0, 0.0));
                            currentPath_.erase(currentPath_.begin());
                        }
                        return false;
                    }
                    else // the target is no longer valid, a new plan needs to be recompute
                    {
                        currentPath_.clear();
                        movementComponent->setVelocity(Geometry::Vec3Df(0.0, 0.0, 0.0));
                    }
                }
                else // The movement action is finished, the entity has reached the target
                {
                    movementComponent->setVelocity(Geometry::Vec3Df(0.0, 0.0, 0.0));
                }
                return true;

            }
            catch (const Ecs::ComponentGroup::UnexistingComponentException& e)
            {
                return true;
            }
        }
        void NavigationSubSystem::treatAction(
            Action::Action* action,
            Ecs::ComponentGroup &components
        ) {
            Action::MoveCloseToTargetAction* moveAction = dynamic_cast<Action::MoveCloseToTargetAction*>(action);
            if(moveAction == NULL)
            {
                setCurrentAction(noAction_);
                return;
            }

            try
            {
                // Get all the needed components
                ConcurrentReader<Geometry::PositionComponent> positionComponent =
                    getConcurrentReader<Ecs::Component, Geometry::PositionComponent>(
                        components.getComponent(Geometry::PositionComponent::Type)
                    );

                ConcurrentReader<TargetingComponent> targetingComponent =
                    getConcurrentReader<Ecs::Component, TargetingComponent>(
                        components.getComponent(TargetingComponent::Type)
                    );

                if(targetingComponent->hasValidTarget())
                {
                    //currentAction_ = moveAction;
                    setCurrentAction(moveAction);
                    Geometry::Vec3Df navigationTarget =
                        targetingComponent->getTargetPosition();
                    // const Geometry::Vec3Df& currentPosition =
                    //     positionComponent->getPosition();
                    // Compute the path to the target

                    currentPath_.clear();
                    // const NavMesh::NavMesh* currentNavMesh = NULL;
                    // Geometry::Vec2Df currentPosition2D =
                    //     Geometry::Vec2Df(currentPosition.getX(), currentPosition.getY());
                    // Geometry::Vec2Df targetPosition2D =
                    //     Geometry::Vec2Df(navigationTarget.getX(), navigationTarget.getY());
                    // if(navMeshes_.getNavMesh(currentPosition2D, currentNavMesh))
                    // {

                    //     Graph::PlanarNode startNode;
                    //     Graph::PlanarNode endNode;
                    //     if(currentNavMesh->getNode(currentPosition2D, startNode)
                    //             && currentNavMesh->getNode(targetPosition2D, endNode))
                    //     {
                    //         Graph::PlanarGraph::NodeCollection path;
                    //         // If a path exists add the current position of the cgaracter and its target position to the path
                    //         if(Graph::BasicAStar(currentNavMesh->getGraph(), startNode, endNode, path))
                    //         {
                    //             for (Graph::PlanarGraph::NodeCollection::const_iterator it = path.begin(); it != path.end(); ++it)
                    //             {
                    //                 Graph::PlanarNode node = (*it);
                    //                 const Geometry::Vec2Df& pos = node.getPosition();
                    //                 currentPath_.push_back(Geometry::Vec3Df(pos.getX(), pos.getY(), 0.0));
                    //             }
                    //         }
                    //     }
                    // }
                    currentPath_.push_back(navigationTarget);
                }
            }
            catch (const Ecs::ComponentGroup::UnexistingComponentException& e)
            {
                return;
            }
        }
    }
}
