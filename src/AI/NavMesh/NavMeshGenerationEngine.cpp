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

#include "NavMeshGenerationEngine.h"
namespace AI
{
    namespace NavMesh
    {
        NavMeshGenerationEngine::NavMeshGenerationEngine() : navMeshes_() , navMeshGenerator_(navMeshes_)
        {
        }

        void NavMeshGenerationEngine::call(const Event::Event& event)
        {
            if (event.getType() == AreaCreatedEvent::Type)
            {
                eventQueue_ << new AreaCreatedEvent(dynamic_cast<const AreaCreatedEvent&>(event));
            }
            else if (event.getType() == ObstacleAddedEvent::Type)
            {
                eventQueue_ << new ObstacleAddedEvent(dynamic_cast<const ObstacleAddedEvent&>(event));
            }
            else if (event.getType() == NavMeshOverEvent::Type)
            {
                eventQueue_ << new NavMeshOverEvent(dynamic_cast<const NavMeshOverEvent&>(event));
            }
        }

        void NavMeshGenerationEngine::run()
        {
            while(!(eventHead_.isEmpty()))
            {
                Event::Event* event = NULL;
                eventHead_ >> event;

                if (event != NULL)
                {
                    if (event->getType() == AreaCreatedEvent::Type)
                    {
                        // Create a new NavMesh
                        const AreaCreatedEvent& areaCreatedEvent = dynamic_cast<const AreaCreatedEvent&>(*event);
                        Geometry::Vec2Df lowerLeftPoint = areaCreatedEvent.getLowerLeftPoint();
                        Geometry::Vec2Df upperRightPoint = areaCreatedEvent.getUpperRightPoint();
                        navMeshGenerator_.createNewNavMesh(lowerLeftPoint, upperRightPoint);
                    }
                    else if (event->getType() == ObstacleAddedEvent::Type)
                    {
                        Obstacle obstacle = dynamic_cast<const ObstacleAddedEvent&>(*event).getObstacle();
                        navMeshGenerator_.updateNavMeshes(obstacle);
                    }
                    else if (event->getType() == NavMeshOverEvent::Type)
                    {
                        const NavMeshOverEvent& navMeshOverEvent = dynamic_cast<const NavMeshOverEvent&>(*event);
                        Geometry::Vec2Df lowerLeftPoint = navMeshOverEvent.getLowerLeftPoint();
                        Geometry::Vec2Df upperRightPoint = navMeshOverEvent.getUpperRightPoint();
                    }
                    delete event;
                }
            }
        }

        void NavMeshGenerationEngine::registerListeners(Event::ListenerRegister& listener)
        {
            listener.put(AreaCreatedEvent::Type, this);
            listener.put(ObstacleAddedEvent::Type, this);
            listener.put(NavMeshOverEvent::Type, this);
        }
    }
}
