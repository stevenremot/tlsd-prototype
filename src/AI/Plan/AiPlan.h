#ifndef AI_PLAN_AIPLAN_H
#define AI_PLAN_AIPLAN_H

#include <vector>

#include "Plan.h"
#include "../Action/Action.h"

namespace AI
{
    namespace Plan
    {
        /**
         * The AiPlan is the sequence of actions the entity have to execute.
         */
        class AiPlan : public Plan
        {
        public:
            AiPlan(const std::vector<Action::Action*>& actionsPlanned) : Plan(), actionsPlanned_(actionsPlanned)
            {
                currentAction_ = actionsPlanned_.begin();
            }
            /**
             * Clean all the pointers in the list.
             */
            ~AiPlan();
            /**
             * Set the current action to the next action in the sequence.
             * If the next action is the last in the list, the plan is complete.
             */
            virtual void goToNextStep();

            Action::Action* getCurrentAction() {return (*currentAction_);}

        private:
            std::vector<Action::Action*> actionsPlanned_;
            std::vector<Action::Action*>::iterator currentAction_;
        };
    }
}
#endif // AI_PLAN_AIPLAN_H
