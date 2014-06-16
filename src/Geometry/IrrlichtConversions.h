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

#ifndef GEOMETRY_IRRLICHTCONVERSIONS_H
#define GEOMETRY_IRRLICHTCONVERSIONS_H

#include <irrlicht/vector3d.h>
#include "Vec3D.h"

namespace Geometry
{
    Vec3Df fromIrrVector3df(const irr::core::vector3df& vec);
    irr::core::vector3df fromVec3Df(const Vec3Df& vec);
}

#endif // GEOMETRY_IRRLICHTCONVERSIONS_H
