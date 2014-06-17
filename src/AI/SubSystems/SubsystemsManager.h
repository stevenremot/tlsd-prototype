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

#ifndef AI_SUBSYSTEM_SUBSYSTEMSMANAGER_H
#define AI_SUBSYSTEM_SUBSYSTEMSMANAGER_H

#include <vector>

#include "Subsystem.h"
#include "../Blackboard.h"
#include "../WorkingMemory.h"

#include "../Action/Action.h"

#include "../../Ecs/Entity.h"
#include "../../Ecs/World.h"

namespace AI
{
    namespace Subsystem
    {
        /**
         * Add, remove and manage the subsystems for the AI module
         */
        class SubSystemsManager
        {
        public:
            SubSystemsManager(Ecs::Entity entity, Ecs::World& world, Blackboard & blackboard, WorkingMemory& memory)
                : entity_(entity), world_(world),
                  blackboard_(blackboard), memory_(memory){}

            void addSubsystem(const Subsystem::SubsystemType & type);
            /**
             * @return NULL if there is no subsystem with this type registered in the manager.
             */
            Subsystem* getSubsystemByType(const Subsystem::SubsystemType& type);

            void updateSubsystems();

            /**
             * Send the action to the subsystem which can execute it.
             */
            void dispatchAction(Action::Action* action);


        private:
            std::vector<Subsystem*> subSystemsList_;
            const Ecs::Entity entity_;
            Ecs::World world_;
            Blackboard& blackboard_;
            WorkingMemory& memory_;
        };
    }

}

#endif // AI_SUBSYSTEM_SUBSYSTEMSMANAGER_H
