#ifndef GEOMETRY_IRRLICHTCONVERSIONS_H
#define GEOMETRY_IRRLICHTCONVERSIONS_H

#include <irrlicht/vector3d.h>
#include <irrlicht/position2d.h>
#include "Vec3D.h"
#include "Vec2D.h"

namespace Geometry
{
    Vec3Df fromIrrVector3df(const irr::core::vector3df& vec);
    irr::core::vector3df fromVec3Df(const Vec3Df& vec);

    Vec2Df fromIrrPosition2df(const irr::core::position2df& pos);
    irr::core::position2df fromVec2Df(const Vec2Df& pos);
}

#endif // GEOMETRY_IRRLICHTCONVERSIONS_H
