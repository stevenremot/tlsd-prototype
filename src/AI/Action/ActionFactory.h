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

#ifndef AI_ACTION_ACTIONFACTORY_H
#define AI_ACTION_ACTIONFACTORY_H

#include "Action.h"
#include "MoveCloseToTargetAction.h"
#include "NoAction.h"

#include "../SubSystems/TargetingComponent.h"

#include "../../Ecs/ComponentGroup.h"
namespace AI
{
    namespace Action
    {

        /**
         * This exception is raised when trying to provide components
         * that do not satisfy types requirements.
         */
        class CannotCreateActionException: public std::exception
        {
        public:
            const char * what() const throw()
            {
                return "Tried to create an action of unknown type";
            }
        };

        class ActionFactory
        {
        public:
            static Action* createAction(const Action::ActionType type, const Ecs::ComponentGroup& components)
            {
                try
                {
                    if(type == MoveCloseToTargetAction::Type)
                    {
                        const Subsystem::TargetingComponent& targetingComponent = static_cast<const Subsystem::TargetingComponent&>(components.getComponent(Subsystem::TargetingComponent::Type));
                        return new MoveCloseToTargetAction(targetingComponent.getTargetPosition());
                    }
                    else if (type == NoAction::Type)
                    {
                        return new NoAction();
                    }
                }
                catch (const Ecs::ComponentGroup::UnexistingComponentException& e)
                {
                    throw CannotCreateActionException();
                }
                throw CannotCreateActionException();
            }
        private:
        };
    }
}

#endif // AI_ACTION_ACTIONFACTORY_H
