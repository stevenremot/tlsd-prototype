#ifndef AI_ACTION_NOACTION_H
#define AI_ACTION_NOACTION_H

#include "Action.h"

namespace AI
{
    namespace Action
    {
        class NoAction : public Action
        {
        public:

            static const Action::ActionType Type;

            NoAction()
                : Action(Type) {}
        };
    }
}
#endif // AI_ACTION_NOACTION_H
