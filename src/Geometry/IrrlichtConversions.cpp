#include "IrrlichtConversions.h"

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

    Vec2Df fromIrrPosition2df(const irr::core::position2df& pos)
    {
        return Vec2Df(pos.X, pos.Y);
    }

    irr::core::position2df fromVec2Df(const Vec2Df& pos)
    {
        return irr::core::position2df(pos.getX(), pos.getY());
    }
}
