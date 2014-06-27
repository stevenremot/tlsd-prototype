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

#include "IrrlichtConversions.h"

namespace Geometry
{
    Vec3Df fromIrrVector3df(const irr::core::vector3df& vec)
    {
        return Vec3Df(vec.Z, vec.X, vec.Y);
    }

    irr::core::vector3df fromVec3Df(const Vec3Df& vec)
    {
        return irr::core::vector3df(vec.getY(), vec.getZ(), vec.getX());
    }

    Vec2Df fromIrrPosition2df(const irr::core::position2df& pos)
    {
        return Vec2Df(pos.X, pos.Y);
    }

    irr::core::position2df fromVec2Df(const Vec2Df& pos)
    {
        return irr::core::position2df(pos.getX(), pos.getY());
    }
}
