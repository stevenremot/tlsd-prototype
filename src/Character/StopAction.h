#ifndef CHARACTER_STOPACTION_H
#define CHARACTER_STOPACTION_H

#include "Action.h"

namespace Character
{
    class StopAction: public Action
    {
    public:
        static const Type Type;

        StopAction():
            Action(Type)
        {}
    };
}

#endif // CHARACTER_STOPACTION_H
