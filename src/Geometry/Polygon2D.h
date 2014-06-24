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

#ifndef GEOMETRY_POLYGON_2D_H
#define GEOMETRY_POLYGON_2D_H

#include <vector>

#include "Vec2D.h"

namespace Geometry
{
    /**
     * Represent a 2D polygon
     *
     * It is basically a sequence of points.
     */
    class Polygon2D
    {
    public:
        Polygon2D(const std::vector<Vec2Df>& points): points_(points)
        {}

        Polygon2D(const Polygon2D& polygon): points_(polygon.points_)
        {}

        const std::vector<Vec2Df>& getPoints() const
        {
            return points_;
        }

        /**
         * Return true if the point is inside the polygon.
         *
         * Works only for a convex polygon.
         */
        bool contains(const Vec2Df& point) const;

        /**
         * Apply an offset operation to the polygon
         *
         * @param value the offset's value. If it is positive, the polygon will
         *              grow. Otherwise it will shrink.
         *
         * @return the offseted polygon
         */
        std::vector<Polygon2D> offset(float value) const;

    private:
            std::vector<Vec2Df> points_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
