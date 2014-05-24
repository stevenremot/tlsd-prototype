#include "AiPlan.h"

using std::vector;

namespace AI
{
    namespace Plan
    {
        AiPlan::~AiPlan()
        {
            // Delete all the pointers to actions
            vector<Action::Action*>::iterator it;
            for(it = actionsPlanned_.begin(); it != actionsPlanned_.end(); ++it)
            {
                delete (*it);
            }
        }

        void AiPlan::goToNextStep()
        {
            if(!isPlanCompleted())
            {
                ++currentAction_;
                if(currentAction_ == actionsPlanned_.end())
                    setPlanCompleted(true);
            }
        }
    }
}
