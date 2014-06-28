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

#ifndef AI_AIMODULE_H
#define AI_AIMODULE_H

#include <vector>

#include "Action/Action.h"
#include "Blackboard.h"
#include "Plan/AiPlan.h"

#include "../Ecs/ComponentGroup.h"

namespace AI
{
    /**
     * Base class computing the sequence of actions to execute for the entity.
     * Override computeNewPlan to implement entity's AI.
     * It retrieves information from the blackboard to choose the most relevant action.
     *
     */
    class AiModule
    {
    public:
        AiModule();

        virtual ~AiModule(){}

        /**
         * Give the entity the possibility to use another action.
         */
        void addAvailableAction(const  Action::Action::ActionType& actionType);

        /**
         * Compute the next sequence of action to execute.
         * Clean up the former plan so you should check if it has been fully executed before computing a new one.
         */
        virtual void computeNewPlan(Ecs::ComponentGroup& components) = 0;

        void cleanPlan()
        {
            if(aiPlan_ != NULL && aiPlan_->isPlanCompleted())
            {
                delete aiPlan_;
                aiPlan_ = NULL;
            }
        }
        void setPlan(Plan::AiPlan* aiPlan) {aiPlan_ = aiPlan;}
        Plan::AiPlan* getPlan() {return aiPlan_;}

    protected:
        const std::vector<Action::Action::ActionType>& getAvailableActions() const {return availableActions_;}

    private:
        std::vector<Action::Action::ActionType> availableActions_;
        Plan::AiPlan* aiPlan_;
    };
}

#endif // AI_AIMODULE_H
