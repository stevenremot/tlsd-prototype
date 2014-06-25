#ifndef PHYSICS_COLLISIONENGINE_H
#define PHYSICS_COLLISIONENGINE_H

#include "AABBCollisionBody.h"
#include "Model3DCollisionBody.h"

namespace Physics
{
    class ANotPositiveException : public std::exception
    {
        const char* what() const throw()
        {
            return "a not positive";
        }
    };

    /**
    *   Collision Engine containing collision response functions and algorithm parameters
    */
    class CollisionEngine
    {
    public:
        CollisionEngine()
        {}

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

        inline bool getAABBCollision(const Geometry::AxisAlignedBoundingBox& aabb1, const Geometry::AxisAlignedBoundingBox& aabb2);

        /**
        *   Intermediate function for the sliding ellipsoid method
        */
        void computeT0AndT1(
            const Geometry::Vec3Df& position,
            const Geometry::Vec3Df& velocity,
            const Geometry::Vec3Df& normal,
            const Geometry::Vec3Df& planePoint,
            float& t0,
            float& t1);

        /**
        *   Solve the quadratic equation a t² + b t + c = 0
        *   @return true if there is one or two solutions
        *   @param[in] a : supposed > 0
        *   @param[out] t1 : lowest root
        */
        bool solveQuadraticEquation(float a, float b, float c, float& x0);

        void resolveVertexCollision(
            const Geometry::Vec3Df& v,
            const Geometry::Vec3Df& ellipsoidCenter,
            const Geometry::Vec3Df& velocity,
            const float& velocitySquaredLength,
            const float& velocityLength,
            Geometry::Vec3Df& intersectionPoint,
            float& intersectionDistance,
            float& t);

        void resolveEdgeCollision(
            const Geometry::Vec3Df& edge,
            const Geometry::Vec3Df& point,
            const Geometry::Vec3Df& ellispoidCenter,
            const Geometry::Vec3Df& velocity,
            const float& velocitySquaredLength,
            const float& velocityLength,
            Geometry::Vec3Df& intersectionPoint,
            float& intersectionDistance,
            float& t);
    };
}

#endif // PHYSICS_COLLISIONENGINE_H
