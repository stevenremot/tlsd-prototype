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

#ifndef AI_NAVMESH_NAVMESHGENERATOREVENT_H
#define AI_NAVMESH_NAVMESHGENERATOREVENT_H

#include "Obstacle.h"

#include "../../Event/Event.h"
#include "../../Geometry/Vec2D.h"

namespace AI
{
    namespace NavMesh
    {
        /**
         * Dispatched when a new chunk is created
         */
        class AreaCreatedEvent: public Event::Event
        {
        public:
            static const Event::Type Type;

            AreaCreatedEvent(Geometry::Vec2Df lowerLeftPoint, Geometry::Vec2Df upperRightPoint)
                : Event::Event(Type), lowerLeftPoint_(lowerLeftPoint), upperRightPoint_(upperRightPoint)
            {}

            Geometry::Vec2Df getLowerLeftPoint() const {return lowerLeftPoint_;}
            Geometry::Vec2Df getUpperRightPoint() const {return upperRightPoint_;}

        private:
            Geometry::Vec2Df lowerLeftPoint_;
            Geometry::Vec2Df upperRightPoint_;
        };

        /**
        * Dispatched when a new obstacle is added to the world
        */
        class ObstacleAddedEvent: public Event::Event
        {
        public:
            static const Event::Type Type;

            ObstacleAddedEvent(Obstacle obstacle): Event::Event(Type), obstacle_(obstacle)
            {}

            Obstacle getObstacle() const
            {
                return obstacle_;
            }

        private:
            Obstacle obstacle_;
        };

        /**
         * Dispatched when all the obstacles have been added to a chunk
         */
        class NavMeshOverEvent: public Event::Event
        {
        public:
            static const Event::Type Type;

            NavMeshOverEvent(Geometry::Vec2Df lowerLeftPoint, Geometry::Vec2Df upperRightPoint)
                : Event::Event(Type), lowerLeftPoint_(lowerLeftPoint), upperRightPoint_(upperRightPoint)
            {}

            Geometry::Vec2Df getLowerLeftPoint() const {return lowerLeftPoint_;}
            Geometry::Vec2Df getUpperRightPoint() const {return upperRightPoint_;}

        private:
            Geometry::Vec2Df lowerLeftPoint_;
            Geometry::Vec2Df upperRightPoint_;
        };
    }
}

#endif // AI_NAVMESH_NAVMESHGENERATOREVENT_H
