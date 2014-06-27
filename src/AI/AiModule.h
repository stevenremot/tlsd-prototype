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
        AiModule(Ecs::ComponentGroup &components, Blackboard& blackboard);

        virtual ~AiModule(){}

        /**
         * Give the entity the possibility to use another action.
         */
        void addAvailableAction(const  Action::Action::ActionType& actionType);

        /**
         * Compute the next sequence of action to execute.
         * Clean up the former plan so you should check if it has been fully executed before computing a new one.
         */
        virtual void computeNewPlan() = 0;

        //void executePlan();
        //std::vector<Action*> getNewPlan() const {return newPlan_;}

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
        Ecs::ComponentGroup& getComponents() {return components_;}
        Blackboard& getBlackboard() {return blackboard_;}
        const std::vector<Action::Action::ActionType>& getAvailableActions() const {return availableActions_;}

    private:
        Ecs::ComponentGroup& components_;
        Blackboard& blackboard_;
        std::vector<Action::Action::ActionType> availableActions_;
        Plan::AiPlan* aiPlan_;
    };
}

#endif // AI_AIMODULE_H
