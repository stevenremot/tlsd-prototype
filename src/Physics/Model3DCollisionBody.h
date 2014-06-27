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

#ifndef PHYSICS_MODEL3DCOLLISIONBODY_H
#define PHYSICS_MODEL3DCOLLISIONBODY_H

#include "CollisionBody.h"
#include "../Graphics/Render/Model3D.h"
#include "../Geometry/AxisAlignedBoundingBox.h"

namespace Physics
{
    /**
    *   CollisionBody for Renderable entities with few polys : it uses the Model3D itself
    */
    class Model3DCollisionBody : public CollisionBody
    {
    public:
        static const Type Type;

        Model3DCollisionBody(const Graphics::Render::Model3D& model, const Geometry::AxisAlignedBoundingBox& aabb):
            CollisionBody(Type),
            model_(model),
            aabb_(aabb)
        {}

        Model3DCollisionBody(const Graphics::Render::Model3D& model, const Geometry::Vec3Df& position):
            CollisionBody(Type),
            model_(model),
            aabb_(Geometry::Vec3Df(), Geometry::Vec3Df())
        {
            setAbsoluteCoordinates(position);
            computeAABB();
        }

        virtual CollisionBody* clone()
        {
            return new Model3DCollisionBody(model_, aabb_);
        }

        const Graphics::Render::Model3D& getModel() const
        {
            return model_;
        }

        const Geometry::AxisAlignedBoundingBox& getAABB() const
        {
            return aabb_;
        }

    private:
        void setAbsoluteCoordinates(const Geometry::Vec3Df& position)
        {
            for (unsigned int i = 0; i < model_.getVertices().size(); i++)
            {
                model_.getVertices().at(i) += position;
            }
        }

        void computeAABB()
        {
            Geometry::Vec3Df origin = model_.getVertices()[0];
            float minX = origin.getX();
            float maxX = origin.getX();
            float minY = origin.getY();
            float maxY = origin.getY();
            float minZ = origin.getZ();
            float maxZ = origin.getZ();

            for (unsigned int i = 0; i < model_.getVertices().size(); i++)
            {
                Geometry::Vec3Df current = model_.getVertices()[i];

                if (current.getX() < minX)
                    minX = current.getX();
                else if (current.getX() > maxX)
                    maxX = current.getX();

                if (current.getY() < minY)
                    minY = current.getY();
                else if (current.getY() > maxY)
                    maxY = current.getY();

                if (current.getZ() < minZ)
                    minZ = current.getZ();
                else if (current.getZ() > maxZ)
                    maxZ = current.getZ();
            }

            origin = Geometry::Vec3Df(minX, minY, minZ);
            Geometry::Vec3Df offset(maxX, maxY, maxZ);

            aabb_ = Geometry::AxisAlignedBoundingBox(origin, offset);
        }

        Graphics::Render::Model3D model_;
        Geometry::AxisAlignedBoundingBox aabb_; // AABB for quick checks
    };
}

#endif // PHYSICS_MODEL3DCOLLISIONBODY_H
