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
            virtual ~AiPlan();
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
