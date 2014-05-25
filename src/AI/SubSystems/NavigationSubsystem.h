#ifndef NAVIGATIONSUBSYSTEM_H
#define NAVIGATIONSUBSYSTEM_H

#include "Subsystem.h"

#include "../../Geometry/PositionComponent.h"
#include "../../Physics/MovementComponent.h"
#include "../../Geometry/Vec3D.h"


namespace AI
{
    namespace Subsystem
    {
        /**
         * Find a path to the target position and update the velocity of the entity to make it reach the target.
         * Entity needs movement and position components to have a navigation system.
         * TODO : abort the movement when the entity cannot reach the target position.
         */
        class NavigationSubSystem : public AI::Subsystem::Subsystem
        {
        public:
            static const Subsystem::SubsystemType Type;

            NavigationSubSystem(Blackboard& blackboard,
                                Geometry::PositionComponent& positionComponent,
                                Physics::MovementComponent& movementComponent);
            ~NavigationSubSystem(){}

            void findPathToGoal();
            virtual bool update();
            virtual void executeAction(Action::Action *action);

        private:
            const Geometry::PositionComponent& positionComponent_;
            Physics::MovementComponent& movementComponent_;
            Geometry::Vec3Df navigationTarget_;
            bool isFinished_;
        };
    }
}

#endif // NAVIGATIONSUBSYSTEM_H
