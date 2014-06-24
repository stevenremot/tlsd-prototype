#include <iostream>

#include "CollisionEngine.h"

using Geometry::AxisAlignedBoundingBox;
using Geometry::Vec3Df;

namespace Physics
{
    inline bool CollisionEngine::getAABBCollision(const AxisAlignedBoundingBox& aabb1, const AxisAlignedBoundingBox& aabb2)
    {
        return     aabb1.getOrigin().getX() < aabb2.getOffset().getX() &&
                   aabb1.getOrigin().getY() < aabb2.getOffset().getY() &&
                   aabb1.getOrigin().getZ() < aabb2.getOffset().getZ() &&
                   aabb2.getOrigin().getX() < aabb1.getOffset().getX() &&
                   aabb2.getOrigin().getY() < aabb1.getOffset().getY() &&
                   aabb2.getOrigin().getZ() < aabb1.getOffset().getZ();
    }

    bool CollisionEngine::getAABBAgainstAABBCollisionResponse(
        const AABBCollisionBody& aabbBody1,
        const AABBCollisionBody& aabbBody2,
        Geometry::Vec3Df& position1,
        const Geometry::Vec3Df& position2)
    {
        AxisAlignedBoundingBox movingAABB = aabbBody1.getTranslatedBoundingBox(position1);
        AxisAlignedBoundingBox otherAABB = aabbBody2.getTranslatedBoundingBox(position2);
        return getAABBCollision(movingAABB, otherAABB);
    }


    bool CollisionEngine::getAABBAgainstModel3DCollisionResponse(
        const AABBCollisionBody& aabbBody,
        const Model3DCollisionBody& modelBody,
        Geometry::Vec3Df& position,
        Geometry::Vec3Df& movementVector)
    {
        AxisAlignedBoundingBox movingAABB = aabbBody.getTranslatedBoundingBox(position);

        if (!getAABBCollision(movingAABB, modelBody.getAABB()))
        {
            return false;
        }

        const std::vector<Vec3Df>& vertices = modelBody.getModel().getVertices();
        const std::vector<Graphics::Render::Face>& faces = modelBody.getModel().getFaces();

        Vec3Df lastPosition = position - movementVector;
        movingAABB = aabbBody.getTranslatedBoundingBox(lastPosition);
        Vec3Df ellipsoidRadius = movingAABB.getExtent() * 0.5;
        Vec3Df ellipsoidCenter = (movingAABB.getOrigin() + ellipsoidRadius) / ellipsoidRadius;
        Vec3Df velocity = movementVector / ellipsoidRadius;

        // computed beforehand
        float velocitySquaredLength = velocity.getSquaredLength();
        float velocityLength = std::sqrt(velocitySquaredLength);

        Vec3Df intersectionPoint = Vec3Df();
        float intersectionDistance = 10000;

        for (unsigned int tri = 0; tri < faces.size(); tri++)
        {
            Vec3Df intersectionPointTri = Vec3Df();
            float intersectionDistanceTri = 10000;

            // to work in the ellipsoid space, positions are divised by ellipsoid radius
            Vec3Df p0 = vertices[faces[tri][0]] / ellipsoidRadius;
            Vec3Df p1 = vertices[faces[tri][1]] / ellipsoidRadius;
            Vec3Df p2 = vertices[faces[tri][2]] / ellipsoidRadius;

            Vec3Df v0 = p1 - p0;
            Vec3Df v1 = p2 - p0;

            Vec3Df n = v0.cross(v1);
            n.normalize();

            float t0 = 0;
            float t1 = 0;
            computeT0AndT1(ellipsoidCenter, velocity, n, p0, t0, t1);

            if (t1 < 0 || t0 > 1)
                continue;

            if (t0 < 0)
                t0 = 0;
            if (t1 > 1)
                t1 = 1;

            Vec3Df planeIntersectionPoint = ellipsoidCenter - n + velocity * t0;

            // compute barycentric coordinates
            Vec3Df v2 = planeIntersectionPoint - p0;
            float dot00 = v0.dot(v0);
            float dot01 = v0.dot(v1);
            float dot02 = v0.dot(v2);
            float dot11 = v1.dot(v1);
            float dot12 = v1.dot(v2);
            float invDenom =  1.0 / (dot00 * dot11 - dot01 * dot01);
            float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
            float v = (dot00 * dot12 - dot01 * dot02) * invDenom;
            float w = 1 - u - v;

            if (u > 0 && v > 0 && w > 0)
            {
                // the point in inside the triangle
                intersectionPointTri = planeIntersectionPoint;
                intersectionDistanceTri = t0 * velocityLength;
            }
            else
            {
                float t = t1;

                resolveVertexCollision(
                    p0,
                    ellipsoidCenter,
                    velocity,
                    velocitySquaredLength,
                    velocityLength,
                    intersectionPointTri,
                    intersectionDistanceTri,
                    t);

                resolveVertexCollision(
                    p1,
                    ellipsoidCenter,
                    velocity,
                    velocitySquaredLength,
                    velocityLength,
                    intersectionPointTri,
                    intersectionDistanceTri,
                    t);

                resolveVertexCollision(
                    p2,
                    ellipsoidCenter,
                    velocity,
                    velocitySquaredLength,
                    velocityLength,
                    intersectionPointTri,
                    intersectionDistanceTri,
                    t);

                resolveEdgeCollision(
                    v0,
                    p0,
                    ellipsoidCenter,
                    velocity,
                    velocitySquaredLength,
                    velocityLength,
                    intersectionPointTri,
                    intersectionDistanceTri,
                    t);

                resolveEdgeCollision(
                    v1,
                    p0,
                    ellipsoidCenter,
                    velocity,
                    velocitySquaredLength,
                    velocityLength,
                    intersectionPointTri,
                    intersectionDistanceTri,
                    t);

                resolveEdgeCollision(
                    p2 - p1,
                    p1,
                    ellipsoidCenter,
                    velocity,
                    velocitySquaredLength,
                    velocityLength,
                    intersectionPointTri,
                    intersectionDistanceTri,
                    t);
            }

            if (intersectionDistanceTri < intersectionDistance)
            {
                intersectionPoint = intersectionPointTri;
                intersectionDistance = intersectionDistanceTri;
            }
        }

        if (intersectionDistance < 10000)
        {
            std::cout << "Collision found : " << intersectionPoint << std::endl;
            // TODO: collision response
        }

        return false;
    }

    void CollisionEngine::computeT0AndT1(
        const Geometry::Vec3Df& position,
        const Geometry::Vec3Df& velocity,
        const Geometry::Vec3Df& normal,
        const Geometry::Vec3Df& planePoint,
        float& t0,
        float& t1)
    {
        float signedDistance = position.dot(normal) - planePoint.dot(normal);
        float dotProduct = normal.dot(velocity);
        if (dotProduct != 0)
        {
            t0 = (1 - signedDistance) / dotProduct;
            t1 = (-1 - signedDistance) / dotProduct;
        }
        else
        {
            if (std::abs(signedDistance) < 1)
            {
                t0 = 0;
                t1 = 1;
            }
            else
            {
                t0 = -1;
                t1 = -1;
            }
        }

        // swap t0 and t1 so that t0 < t1
        if (t1 < t0)
        {
            float tmp = t0;
            t0 = t1;
            t1 = tmp;
        }
    }

    bool CollisionEngine::solveQuadraticEquation(
        float a,
        float b,
        float c,
        float& x)
    {
        float delta = b*b - 4*a*c;
        float root = 0;

        if (delta < 0)
            return false;
        else if (delta == 0)
            root = -b/(2*a);
        else
            root = -b - std::sqrt(delta) / (2*a);

        // for our algorithm we discard negative solutions
        if (root < 0)
            return false;
        else if (root < x)
        {
            x = root;
            return true;
        }

        return false;
    }

    void CollisionEngine::resolveEdgeCollision(
        const Geometry::Vec3Df& e,
        const Geometry::Vec3Df& p,
        const Geometry::Vec3Df& ellipsoidCenter,
        const Geometry::Vec3Df& velocity,
        const float& velocitySquaredLength,
        const float& velocityLength,
        Geometry::Vec3Df& intersectionPoint,
        float& intersectionDistance,
        float& t)
    {
        float edgeSquaredLength = e.getSquaredLength();
        Vec3Df baseToVertex = p - ellipsoidCenter;
        float doteb = e.dot(baseToVertex);
        float dotev = e.dot(velocity);
        float a = edgeSquaredLength * velocitySquaredLength - dotev*dotev;
        float b = 2 * (dotev*doteb)
                  - edgeSquaredLength * 2 * (velocity.dot(baseToVertex));
        float c = doteb*doteb - edgeSquaredLength * (1 - baseToVertex.getSquaredLength());

        float lastT = t;
        if (solveQuadraticEquation(a,b,c,t))
        {
            float lineCoordinate = (dotev * t - doteb) / edgeSquaredLength;
            if (lineCoordinate > 0 && lineCoordinate < 1)
            {
                intersectionPoint = p + e * lineCoordinate;
                intersectionDistance = t * velocityLength;
            }
            else
                t = lastT;
        }
    }

    void CollisionEngine::resolveVertexCollision(
        const Geometry::Vec3Df& v,
        const Geometry::Vec3Df& ellipsoidCenter,
        const Geometry::Vec3Df& velocity,
        const float& velocitySquaredLength,
        const float& velocityLength,
        Geometry::Vec3Df& intersectionPoint,
        float& intersectionDistance,
        float& t)
    {
        float a = velocitySquaredLength;
        float b = 2 * (velocity.dot(ellipsoidCenter - v));
        float c = (ellipsoidCenter - v).getSquaredLength() - 1;
        if (solveQuadraticEquation(a,b,c,t))
        {
            intersectionPoint = v;
            intersectionDistance = t * velocityLength;
        }
    }
}
