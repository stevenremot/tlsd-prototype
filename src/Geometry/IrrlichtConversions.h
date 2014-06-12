#ifndef GEOMETRY_IRRLICHTCONVERSIONS_H
#define GEOMETRY_IRRLICHTCONVERSIONS_H

#include <irrlicht/vector3d.h>
#include "Vec3D.h"

namespace Geometry
{
    Vec3Df fromIrrVector3df(const irr::core::vector3df& vec)
    {
        return Vec3Df(vec.X, vec.Z, vec.Y);
    }

    irr::core::vector3df fromVec3Df(const Vec3Df& vec)
    {
        return irr::core::vector3df(vec.getX(), vec.getZ(), vec.getY());
    }
}

#endif // GEOMETRY_IRRLICHTCONVERSIONS_H
