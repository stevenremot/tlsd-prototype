#ifndef PHYSICS_COLLISIONENGINE_H
#define PHYSICS_COLLISIONENGINE_H

#include "AABBCollisionBody.h"
#include "Model3DCollisionBody.h"

namespace Physics
{
    /**
    *   Collision Engine containing collision response functions and algorithm parameters
    */
    class CollisionEngine
    {
    public:
        CollisionEngine();

        /**
        *   Apply sliding ellipsoid against polygons collision response
        */
        bool getAABBAgainstModel3DCollisionResponse(
            const AABBCollisionBody& aabbBody,
            const Model3DCollisionBody& modelBody,
            Geometry::Vec3Df& position,
            Geometry::Vec3Df& movementVector
        );

        /**
        *   Simple AABB based collision response
        */
        bool getAABBAgainstAABBCollisionResponse(
            const AABBCollisionBody& aabbBody1,
            const AABBCollisionBody& aabbBody2,
            Geometry::Vec3Df& position1,
            const Geometry::Vec3Df& position2
        );
    };
}

#endif // PHYSICS_COLLISIONENGINE_H
