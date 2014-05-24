#ifndef AI_AIMODULE_H
#define AI_AIMODULE_H

#include <vector>

#include "Action/Action.h"
#include "Blackboard.h"
#include "Plan/AiPlan.h"

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
        AiModule(Blackboard& blackboard);

        /**
         * Give the entity the possibility to use another action.
         */
        void addAvailableAction(const  Action::Action::ActionType& actionType);

        /**
         * Compute the next sequence of action to execute.
         * Clean up the former plan so you should check if it has been fully executed before computing a new one.
         */
        virtual void computeNewPlan() = 0;
        //std::vector<Action*> getNewPlan() const {return newPlan_;}

    protected:
        Blackboard& getBlackboard() {return blackboard_;}
        const std::vector<Action::Action::ActionType>& getAvailableActions() const {return availableActions_;}
        void setPlan(Plan::AiPlan* aiPlan) {aiPlan_ = aiPlan;}
    private:
        Blackboard& blackboard_;
        std::vector<Action::Action::ActionType> availableActions_;
        Plan::AiPlan* aiPlan_;
    };
}

#endif // AI_AIMODULE_H
