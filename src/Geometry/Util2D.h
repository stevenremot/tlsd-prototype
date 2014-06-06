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

#ifndef GEOMETRY_UTIL_2D_H
#define GEOMETRY_UTIL_2D_H

#include "Vec2D.h"

namespace Geometry
{
    /**
     * Return a median vector of v1 and v2.
     *
     * v1's end is the same point than v2's start
     *
     * The median direction is toward the "left" of v1.
     */
    Vec2Df getMedian(const Vec2Df& v1, const Vec2Df& v2)
    {
        Vec2Df o1 = v1.getOrthogonal().normalize();
        Vec2Df o2 = v2.getOrthogonal().normalize();
        return (o2 + o1).normalize();
    }
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
