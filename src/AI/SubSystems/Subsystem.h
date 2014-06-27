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

#ifndef AI_SUBSYSTEM_SUBSYSTEM_H
#define AI_SUBSYSTEM_SUBSYSTEM_H

#include <string>
#include <vector>

#include "../Blackboard.h"
#include "../MemoryFact.h"

#include "../Action/Action.h"
#include "../Action/NoAction.h"

#include "../../Ecs/ComponentGroup.h"
//#include "../../Ecs/Component.h"

/**
 * Base class for the subsystems of the AI module.
 * Warning : this class has nothing to do with Ecs::System!
 */
namespace AI
{
    namespace Subsystem
    {
        class Subsystem
        {
        public:
            typedef std::string SubsystemType;

            Subsystem(const SubsystemType & subsystemType)
                : subsystemType_(subsystemType)
            {
                noAction_ = new Action::NoAction();
                currentAction_ = NULL;
                setCurrentAction(noAction_);
            }
            virtual ~Subsystem(){}
            virtual bool update(Ecs::ComponentGroup& components) = 0;
            void reset()
            {
                // It's ok to delete the current action because it's a clone of the action in the aiplan
                if(currentAction_ != NULL)
                    delete currentAction_;
                setCurrentAction(noAction_);
            }

            virtual void treatAction(Action::Action* action, const Ecs::ComponentGroup& components) = 0;

            const SubsystemType & getSubsystemType() const
            {
                return subsystemType_;
            }

        protected:
            const Action::NoAction* noAction_;

            const Action::Action* getCurrentAction() const {return currentAction_;}
            void setCurrentAction(const Action::Action* action)
            {
                /*
                if(currentAction_ != NULL)
                {
                    delete currentAction_;
                    currentAction_ = NULL;
                }
                */
                currentAction_ = action->clone();
            }

        private:
            SubsystemType subsystemType_;
            const Action::Action* currentAction_;
        };
    }
}



#endif // AI_SUBSYSTEM_SUBSYSTEM_H
