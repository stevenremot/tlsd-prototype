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

#ifndef PHYSICS_AABB_COLLISION_BODY_H
#define PHYSICS_AABB_COLLISION_BODY_H

#include "CollisionBody.h"
#include "../Geometry/AxisAlignedBoundingBox.h"

namespace Physics
{
    class AABBCollisionBody: public CollisionBody
    {
    public:
        static const Type Type;

        AABBCollisionBody(const Geometry::AxisAlignedBoundingBox& bbox):
            CollisionBody(Type),
            boundingBox_(bbox)
        {}

        virtual CollisionBody* clone()
        {
            return new AABBCollisionBody(boundingBox_);
        }

        const Geometry::AxisAlignedBoundingBox& getBoundingBox() const
        {
            return boundingBox_;
        }

        Geometry::AxisAlignedBoundingBox getTranslatedBoundingBox(const Geometry::Vec3Df& translation) const
        {
            return Geometry::AxisAlignedBoundingBox(
                       boundingBox_.getOrigin() + translation,
                       boundingBox_.getOffset() + translation
                   );
        }

    private:
        Geometry::AxisAlignedBoundingBox boundingBox_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
