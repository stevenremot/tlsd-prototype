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

#include "Polygon2D.h"

#include "clipper.hpp"

using std::vector;
using ClipperLib::Path;
using ClipperLib::IntPoint;


namespace Geometry
{
    const float MultiplyCoef = 1e6;

    Path vectorToPath(const vector<Vec2Df>& points)
    {
        Path p;
        for (unsigned int i = 0; i < points.size(); i++)
        {
            const Vec2Df& v = points[i] * MultiplyCoef;
            p << IntPoint(v.getX(), v.getY());
        }
        return p;
    }

    vector<Vec2Df> pathToVector(const Path& path)
    {
        vector<Vec2Df> vec;
        for (unsigned int i = 0; i < path.size(); i++)
        {
            const IntPoint& p = path[i];
            vec.push_back(Vec2Df(p.X, p.Y) / MultiplyCoef);
        }
        return vec;
    }

    bool Polygon2D::contains(const Vec2Df& point) const
    {
        float side;
        unsigned int length = points_.size();

        for (unsigned int i = 0; i < length; i++)
        {
            const Vec2Df& p1 = points_[i];
            const Vec2Df& p2 = points_[(i + 1 + length) % length];
            const Vec2Df d1 = p2 - p1;
            const Vec2Df d2 = point - p1;

            const float currentSide = d1.getX() * d2.getY() - d1.getY() * d2.getX();

            if (i == 0)
            {
                side = currentSide;
            }
            else
            {
                if ((side < 0 && currentSide >= 0) ||
                    (side >= 0 && currentSide < 0))
                {
                    return false;
                }
            }
        }

        return true;
    }

    std::vector<Polygon2D> Polygon2D::offset(float value) const
    {
        Path p = vectorToPath(points_);
        ClipperLib::Paths result;
        ClipperLib::ClipperOffset co;
        co.AddPath(p, ClipperLib::jtMiter, ClipperLib::etClosedPolygon);
        co.Execute(result, value * MultiplyCoef);

        std::vector<Polygon2D> polygons;
        for (unsigned int i = 0; i < result.size(); i++)
        {
            polygons.push_back(pathToVector(result[i]));
        }

        return polygons;
    }
}
