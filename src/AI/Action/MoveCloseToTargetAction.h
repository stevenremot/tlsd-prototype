#ifndef MOVECLOSETOTARGETACTION_H
#define MOVECLOSETOTARGETACTION_H

#include "Action.h"
#include "../../Geometry/Vec3D.h"

namespace AI
{
    namespace Action
    {
        class MoveCloseToTargetAction : public Action
        {
        public:

            static const Action::ActionType Type;

            MoveCloseToTargetAction(const Geometry::Vec3Df & targetPosition)
                : Action(Type), targetPosition_(targetPosition) {}

            const Geometry::Vec3Df & getTargetPosition() const {return targetPosition_;}

        private:
            Geometry::Vec3Df targetPosition_;
        };
    }
}

#endif // MOVECLOSETOTARGETACTION_H
