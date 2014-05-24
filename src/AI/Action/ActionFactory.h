#ifndef ACTIONFACTORY_H
#define ACTIONFACTORY_H

#include "Action.h"
#include "MoveCloseToTargetAction.h"
#include "NoAction.h"
#include "../Blackboard.h"

namespace AI
{
    namespace Action
    {
        class ActionFactory
        {
        public:
            static Action* createAction(const Action::ActionType type, const Blackboard& blackboard)
            {
                if(type == MoveCloseToTargetAction::Type)
                {
                    return new MoveCloseToTargetAction(blackboard.getNavigationTarget());
                }
                else if (type == NoAction::Type)
                {
                    return new NoAction();
                }
                return NULL;
            }
        private:
        };
    }
}

#endif // ACTIONFACTORY_H
