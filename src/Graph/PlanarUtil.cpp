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

#include "PlanarUtil.h"

using Geometry::Vec2Df;

namespace Graph
{
    bool isBetween(const Vec2Df& baseDirection,
                   const Vec2Df& nextDirection,
                   const Vec2Df& consideredDirection,
                   Direction clockwise)
    {
        const bool isConvex = nextDirection.dot(baseDirection.getOrthogonal()) >= 0;
        const Vec2Df consideredOrthogonal = consideredDirection.getOrthogonal();

        const float nextDotCons = nextDirection.dot(consideredOrthogonal);
        const float baseDotCons = baseDirection.dot(consideredOrthogonal);

        if (clockwise == ClockwiseDirection)
        {
            if ((isConvex && (nextDotCons >= 0 || baseDotCons >= 0)) ||
                (!isConvex && (nextDotCons) >= 0 && baseDotCons >= 0))
            {
                return true;
            }
            return false;
        }
        else
        {
            if ((isConvex && nextDotCons <= 0 && baseDotCons <= 0) ||
                (!isConvex && (nextDotCons <= 0 || baseDotCons <= 0)))
            {
                return true;
            }
            return false;
        }

        return false;
    }
}
