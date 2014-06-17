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

#ifndef AI_NAVMESH_OBSTACLE_H
#define AI_NAVMESH_OBSTACLE_H

#include "../../Geometry/Vec2D.h"

namespace AI
{
    namespace NavMesh
    {
        /**
         * Temp class representing a bounding box
         */
        class Rectangle
        {
        public:
            Rectangle (const Geometry::Vec2Df& lowerLeftPoint, const  Geometry::Vec2Df& upperRightPoint)
                : lowerLeftPoint_(lowerLeftPoint), upperRightPoint_(upperRightPoint)
            {}

            /**
             * Intersection rectangle-rectangle
             */
            bool intersect(const Rectangle& rect) const
            {
                float x1 = lowerLeftPoint_.getX();
                float y1 = lowerLeftPoint_.getY();
                float width1 = (upperRightPoint_ -lowerLeftPoint_).getX();
                float height1 = (upperRightPoint_ -lowerLeftPoint_).getY();

                float x2 = rect.lowerLeftPoint_.getX();
                float y2 = rect.lowerLeftPoint_.getY();
                float width2 = (rect.upperRightPoint_ -rect.lowerLeftPoint_).getX();
                float height2 = (rect.upperRightPoint_ -rect.lowerLeftPoint_).getY();

                return !(x1 +width1 < x2 || x2 + width2 < x1
                        || y1 + height1 < y2 || y2 + height2 < y1);
            }


            const Geometry::Vec2Df& getLowerLeftPoint() const {return lowerLeftPoint_;}
            const Geometry::Vec2Df& getUpperRightPoint() const {return upperRightPoint_;}

            bool operator< (const Rectangle& rectangle) const
            {
                return (lowerLeftPoint_.getX() < rectangle.lowerLeftPoint_.getX());
            }

        private:
            Geometry::Vec2Df lowerLeftPoint_;
            Geometry::Vec2Df upperRightPoint_;
        };

        /**
         * Temp class for obstacles
         */
        class Obstacle
        {
        public:

            Obstacle(const Geometry::Vec2Df& lowerLeftPoint, const Geometry::Vec2Df& upperRightPoint)
                : boundingBox_(lowerLeftPoint, upperRightPoint)
            {
            }

            const Rectangle& getBoundingBox() const {return boundingBox_;}
        private:
            Rectangle boundingBox_;

        };
    }
}

#endif // AI_NAVMESH_OBSTACLE_H
