#include "AiModule.h"

using std::vector;

namespace AI
{
    AiModule::AiModule(Ecs::ComponentGroup& components, Blackboard &blackboard)
        : components_(components), blackboard_(blackboard), aiPlan_(NULL)
    {
    }

    void AiModule::addAvailableAction(const Action::Action::ActionType& actionType)
    {
        // Check if the action is already in the list.
        vector<AI::Action::Action::ActionType>::iterator it;
        for(it = availableActions_.begin(); it != availableActions_.end(); ++it)
        {
            if((*it) == actionType)
                return;
        }
        // Add the action's type to the list of available actions
        availableActions_.push_back(actionType);
    }

    /*
    void AiModule::executePlan()
    {
        if(aiPlan_ ==  NULL || aiPlan_->isPlanCompleted())
            return;

    }
    */
}
