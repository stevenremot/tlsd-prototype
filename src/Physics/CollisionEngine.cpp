#include "CollisionEngine.h"

using Geometry::AxisAlignedBoundingBox;

namespace Physics
{
    bool CollisionEngine::getAABBCollision(const AxisAlignedBoundingBox& aabb1, const AxisAlignedBoundingBox& aabb2)
    {
        return !(
                   aabb1.getOrigin().getX() > aabb2.getOffset().getX() ||
                   aabb1.getOrigin().getY() > aabb2.getOffset().getY() ||
                   aabb1.getOrigin().getZ() > aabb2.getOffset().getZ() ||
                   aabb2.getOrigin().getX() > aabb1.getOffset().getX() ||
                   aabb2.getOrigin().getY() > aabb1.getOffset().getY() ||
                   aabb2.getOrigin().getZ() > aabb1.getOffset().getZ()
               );
    }

    bool CollisionEngine::getAABBAgainstModel3DCollisionResponse(
        const AABBCollisionBody& aabbBody,
        const Model3DCollisionBody& modelBody,
        Geometry::Vec3Df& position,
        Geometry::Vec3Df& movementVector)
    {
        AxisAlignedBoundingBox movingAABB = aabbBody.getTranslatedBoundingBox(position);

        if (getAABBCollision(movingAABB, modelBody.getAABB()))
        {
            position -= movementVector;
            return true;
        }

        return false;
    }
}
