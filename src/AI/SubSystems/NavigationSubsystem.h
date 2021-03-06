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

#ifndef AI_SUBSYSTEM_NAVIGATIONSUBSYSTEM_H
#define AI_SUBSYSTEM_NAVIGATIONSUBSYSTEM_H

#include "../Action/NoAction.h"
#include "Subsystem.h"
#include "../NavMesh/NavMeshContainer.h"
#include "../../Event/EventQueue.h"

#include "../../Geometry/Vec3D.h"


namespace AI
{
    namespace Subsystem
    {

        /**
         * Find a path to the target position and update the velocity of the entity to make it reach the target.
         * Entity needs movement and position components to have a navigation system.
         * TODO : abort the movement when the entity cannot reach the target position.
         */
        class NavigationSubSystem : public AI::Subsystem::Subsystem
        {
        public:
            static const Subsystem::SubsystemType Type;

            typedef std::vector<Geometry::Vec3Df> Path;

            NavigationSubSystem(Event::EventQueue& eventQueue);
            ~NavigationSubSystem(){}

            void findPathToGoal();
            virtual bool update(Ecs::ComponentGroup& components);
            virtual void treatAction(
                Action::Action* action,
                Ecs::ComponentGroup& components
            );

        private:
            //Action::NoAction* defaultAction_;
            Path currentPath_;
            Event::EventQueue& eventQueue_;
            //Action::Action* currentAction_;
        };
    }
}

#endif // AI_SUBSYSTEM_NAVIGATIONSUBSYSTEM_H
