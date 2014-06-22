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

#include "AiModule.h"

using std::vector;

namespace AI
{
    AiModule::AiModule(const Ecs::ComponentGroup &components, Blackboard &blackboard)
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
