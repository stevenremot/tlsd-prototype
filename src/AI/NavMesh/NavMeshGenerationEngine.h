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

#ifndef AI_NAVMESH_NAVMESHGENERATIONENGINE_H
#define AI_NAVMESH_NAVMESHGENERATIONENGINE_H

#include "NavMeshContainer.h"
#include "NavMeshGenerator.h"
#include "NavMeshGeneratorEvent.h"

#include "../../Event/EventListenerInterface.h"
#include "../../Event/ListenerRegister.h"
#include "../../Event/EventQueue.h"
#include "../../Threading/ThreadableInterface.h"

namespace AI
{
    namespace NavMesh
    {
        class NavMeshGenerationEngine : public Event::EventListenerInterface,
                                        public Threading::ThreadableInterface
        {
        public:
            NavMeshGenerationEngine();

            virtual void call(const Event::Event& event);

            virtual void run();

            void registerListeners(Event::ListenerRegister& listener);

            const NavMeshContainer& getNavMeshes() const {return navMeshes_;}
            NavMeshContainer getNavMeshes() {return navMeshes_;}

        private:
            NavMeshContainer navMeshes_;
            NavMeshGenerator navMeshGenerator_;

            Event::EventQueue eventQueue_;
            Event::EventHead eventHead_;
        };
    }
 }
#endif // AI_NAVMESH_NAVMESHGENERATIONENGINE_H
