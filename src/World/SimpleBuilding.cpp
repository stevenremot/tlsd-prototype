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

#include "SimpleBuilding.h"

using Geometry::Vec2Df;
using Geometry::Vec3Df;
using Geometry::Polygon2D;
using Graphics::Render::Model3D;
using Graphics::Render::Face;

namespace World
{
    void SimpleBuilding::updateModel()
    {
        // TODO split in 2 functions
        std::vector<Vec3Df> vertices;
        std::vector<Face> faces;

        const std::vector<Vec2Df>& points = base_.getPoints();
        const unsigned int length = points.size();

        // Building walls
        unsigned int baseIndex = 0;
        for (unsigned int i = 0; i < length; i++)
        {
            const Vec2Df& p1 = points[i];
            const Vec2Df& p2 = points[(i + 1) % length];

            vertices.push_back(Vec3Df(p1.getX(), p1.getY(), 0));
            vertices.push_back(Vec3Df(p2.getX(), p2.getY(), 0));
            vertices.push_back(Vec3Df(p2.getX(), p2.getY(), wallHeight_));
            vertices.push_back(Vec3Df(p1.getX(), p1.getY(), wallHeight_));

            faces.push_back(Face(baseIndex, baseIndex + 1, baseIndex + 2, wallColor_));
            faces.push_back(Face(baseIndex, baseIndex + 2, baseIndex + 3, wallColor_));
            baseIndex += 4;
        }

        // Building roof
        Polygon2D roofBase = base_.offset(0.2)[0];
        Vec2Df center;

        const std::vector<Vec2Df>& roofPoints = roofBase.getPoints();
        const unsigned int roofLength = roofPoints.size();

        // Building base of the roof
        for (unsigned int i = 0; i < roofLength; i++)
        {
            const Vec2Df& point = roofPoints[i];
            vertices.push_back(Vec3Df(point.getX(), point.getY(), wallHeight_));
            center += point;
        }

        center /= roofLength;

        for (unsigned int currentIndex = 1; currentIndex < roofLength - 1; currentIndex++)
        {
            faces.push_back(Face(
                                baseIndex,
                                baseIndex + currentIndex,
                                baseIndex + currentIndex + 1,
                                roofColor_
                            ));
        }

        baseIndex += roofLength;

        // Building roof top
        for (unsigned int i = 0; i < roofLength; i++)
        {
            const Vec2Df& p1 = roofPoints[i];
            const Vec2Df& p2 = roofPoints[(i + 1) % roofLength];

            vertices.push_back(Vec3Df(p1.getX(), p1.getY(), wallHeight_));
            vertices.push_back(Vec3Df(p2.getX(), p2.getY(), wallHeight_));
            vertices.push_back(Vec3Df(
                                   center.getX(),
                                   center.getY(),
                                   wallHeight_ + roofHeight_));

            faces.push_back(Face(baseIndex, baseIndex + 2, baseIndex + 1, roofColor_));
            baseIndex += 3;
        }

        model_ = Model3D(vertices, faces);
    }

}
