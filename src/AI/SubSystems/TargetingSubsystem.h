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

#ifndef AI_SUBSYSTEM_TARGETINGSUBSYSTEM_H
#define AI_SUBSYSTEM_TARGETINGSUBSYSTEM_H

#include "Subsystem.h"
#include "../WorkingMemory.h"
#include "../../Ecs/Entity.h"

namespace AI
{
    namespace Subsystem
    {
        /**
         * This subsystem retrieves memory facts from working memory to set the current target of the entity.
         *
         * The choosen target is based on the memory fact with the highest belief degree.
         */
        class TargetingSubsystem : public Subsystem
        {
        public:

            static const Subsystem::SubsystemType Type;

            TargetingSubsystem(Blackboard& blackboard, WorkingMemory& memory);
            ~TargetingSubsystem();

            virtual void executeAction(Action::Action*){}

            virtual bool update();

        private:
            WorkingMemory& memory_;

            Ecs::Entity targetId_;
        };
    }
}
#endif // AI_SUBSYSTEM_TARGETINGSUBSYSTEM_H
