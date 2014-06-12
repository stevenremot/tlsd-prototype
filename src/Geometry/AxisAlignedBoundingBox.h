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

#ifndef GEOMETRY_AXIS_ALIGNED_BOUNDING_BOX_H
#define GEOMETRY_AXIS_ALIGNED_BOUNDING_BOX_H

#include "Vec3D.h"

namespace Geometry
{
    /**
     * A simple bounding box class.
     */
    class AxisAlignedBoundingBox
    {
    public:
        AxisAlignedBoundingBox(const Vec3Df& origin, const Vec3Df& offset):
            origin_(origin),
            offset_(offset)
        {}

        AxisAlignedBoundingBox(const AxisAlignedBoundingBox& bbox):
            origin_(bbox.origin_),
            offset_(bbox.offset_)
        {}

        const Vec3Df& getOrigin() const
        {
            return origin_;
        }

        const Vec3Df& getOffset() const
        {
            return offset_;
        }

        void setOrigin(const Vec3Df& origin)
        {
            origin_ = origin;
        }

        void setOffset(const Vec3Df& offset)
        {
            offset_ = offset;
        }

    private:
        Vec3Df origin_;
        Vec3Df offset_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
