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

#include "SimpleTree.h"

using Geometry::Vec2Df;
using Geometry::Vec3Df;
using Graphics::Render::Model3D;
using Graphics::Render::Face;

namespace World
{
    void SimpleTree::updateModel()
    {
        // TODO Split into several functions
        std::vector<Vec3Df> vertices;
        std::vector<Face> faces;
        std::vector<Vec2Df> base;

        // Building trunc
        base.push_back(Vec2Df(-truncWidth_/2.0, -truncWidth_/2.0));
        base.push_back(Vec2Df(truncWidth_/2.0, -truncWidth_/2.0));
        base.push_back(Vec2Df(truncWidth_/2.0, truncWidth_/2.0));
        base.push_back(Vec2Df(-truncWidth_/2.0, truncWidth_/2.0));

        const unsigned int length = base.size();

        unsigned int baseIndex = 0;

        for (unsigned int i = 0; i < length; i++)
        {
            const Vec2Df& p1 = base[i];
            const Vec2Df& p2 = base[(i + 1) % length];

            vertices.push_back(Vec3Df(p1.getX(), p1.getY(), -2));
            vertices.push_back(Vec3Df(p2.getX(), p2.getY(), -2));
            vertices.push_back(Vec3Df(p2.getX(), p2.getY(), truncHeight_));
            vertices.push_back(Vec3Df(p1.getX(), p1.getY(), truncHeight_));

            faces.push_back(Face(baseIndex, baseIndex + 2, baseIndex + 1, truncColor_));
            faces.push_back(Face(baseIndex, baseIndex + 3, baseIndex + 2, truncColor_));
            baseIndex += 4;
        }

        // Building leaves base
        std::vector<Vec2Df> leavesBase;

        leavesBase.push_back(Vec2Df(-leavesWidth_/2.0 + offset_, -leavesWidth_/2.0));
        leavesBase.push_back(Vec2Df(leavesWidth_/2.0 + offset_, -leavesWidth_/2.0));
        leavesBase.push_back(Vec2Df(leavesWidth_/2.0 + offset_, leavesWidth_/2.0));
        leavesBase.push_back(Vec2Df(-leavesWidth_/2.0 + offset_, leavesWidth_/2.0));

        const unsigned int leavesLength = leavesBase.size();

        for (unsigned int i = 0; i < leavesLength; i++)
        {
            const Vec2Df& point = leavesBase[i]; 
            vertices.push_back(Vec3Df(point.getX(), point.getY(), truncHeight_));
        }

        for (unsigned int currentIndex = 1; currentIndex < leavesLength - 1; currentIndex++)
        {
            faces.push_back(Face(
                                baseIndex,
                                baseIndex + currentIndex,
                                baseIndex + currentIndex + 1,
                                leavesColor_
                            ));
        }

        baseIndex += leavesLength;

        // Building leaves
        for (unsigned int i = 0; i < leavesLength; i++)
        {
            const Vec2Df& p1 = leavesBase[i];
            const Vec2Df& p2 = leavesBase[(i + 1) % leavesLength];

            vertices.push_back(Vec3Df(p1.getX(), p1.getY(), truncHeight_));
            vertices.push_back(Vec3Df(p2.getX(), p2.getY(), truncHeight_));
            vertices.push_back(Vec3Df(p2.getX(), p2.getY(), truncHeight_ + leavesHeight_));
            vertices.push_back(Vec3Df(p1.getX(), p1.getY(), truncHeight_ + leavesHeight_));

            faces.push_back(Face(baseIndex, baseIndex + 2, baseIndex + 1, leavesColor_));
            faces.push_back(Face(baseIndex, baseIndex + 3, baseIndex + 2, leavesColor_));
            baseIndex += 4;
        }

        // Building leaves top
        for (unsigned int i = 0; i < leavesLength; i++)
        {
            const Vec2Df& point = leavesBase[i]; 
            vertices.push_back(Vec3Df(point.getX(), point.getY(), truncHeight_ + leavesHeight_));
        }

        for (unsigned int currentIndex = 1; currentIndex < leavesLength - 1; currentIndex++)
        {
            faces.push_back(Face(
                                baseIndex,
                                baseIndex + currentIndex + 1,
                                baseIndex + currentIndex,
                                leavesColor_
                            ));
        }

        model_ = Model3D(vertices, faces);
    }
}
