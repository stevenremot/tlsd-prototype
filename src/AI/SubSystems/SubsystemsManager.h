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
#include "../NavMesh/NavMeshContainer.h"

#include "../Action/Action.h"

#include "../../Ecs/Entity.h"
#include "../../Ecs/World.h"
#include "../../Event/EventQueue.h"

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
            SubSystemsManager(Event::EventQueue& eventQueue):
                eventQueue_(eventQueue)
            {}

            ~SubSystemsManager();

            void addSubsystem(const Subsystem::SubsystemType& type);
            /**
             * @return NULL if there is no subsystem with this type registered in the manager.
             */
            Subsystem* getSubsystemByType(const Subsystem::SubsystemType& type);

            /**
             * Update all the subsystems sequentially
             * Return true if all the subsystems don't need to be updated anymore for the moment
             */
            bool updateSubsystems(Ecs::ComponentGroup& components);

            void resetSubsystems();

            /**
             * Send the action to set the subsystem which can execute it.
             */
            void dispatchAction(Action::Action* action, Ecs::ComponentGroup& components);


        private:
            std::vector<Subsystem*> subSystemsList_;
            Event::EventQueue& eventQueue_;
        };
    }

}

#endif // AI_SUBSYSTEM_SUBSYSTEMSMANAGER_H
