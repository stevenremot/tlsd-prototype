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

#include "geometry.h"

#include <iostream>

#include "../Geometry/Vec3D.h"
#include "../Geometry/Vec2D.h"
#include "../Geometry/Polygon2D.h"

using std::cout;
using std::endl;
using std::vector;

using Geometry::Vec2Df;
using Geometry::Vec3Df;
using Geometry::Polygon2D;

namespace GeometryTest
{
    void testVectors()
    {
        Vec2Df v1(1, 2);
        Vec2Df v2(4, 5);

        cout << v1 + v2 << endl;
        cout << v1 - v2 << endl;
        cout << v1 * v2 << endl;
        cout << v1 * 4 << endl;
        cout << -v1 << endl;
        cout << v1.getLength() << endl;

        std::vector<float> orientations;
        std::vector<float> lengths;

        orientations.push_back(M_PI / 4.0);
        lengths.push_back(5.0);

        orientations.push_back(M_PI);
        lengths.push_back(1);

        orientations.push_back(0);
        lengths.push_back(0.5);

        orientations.push_back(M_PI / 6.0);
        lengths.push_back(1.0);

        orientations.push_back(-M_PI / 2.0);
        lengths.push_back(5.0);

        orientations.push_back(M_PI / 2.0);
        lengths.push_back(5.0);

        for (unsigned int i = 0; i < orientations.size(); i++)
        {
            Vec2Df v = Vec2Df::fromPolar(orientations[i], lengths[i]);
            if (v.getOrientation() != orientations[i] ||
                v.getLength() != lengths[i])
            {
                cout << "Vec2D : wrong polar : "
                     << "Got (" << v.getOrientation() << ", " << v.getLength() << "), "
                     << "Exp (" << orientations[i] << ", " << lengths[i] << ")" << endl;
            }
        }

        Vec3Df v3(1, 2, 3);
        Vec3Df v4(4, 5, 6);

        cout << v3 + v4 << endl;
        cout << v3 - v4 << endl;
        cout << v3 * v4 << endl;
        cout << v3 * 4 << endl;
        cout << -v3 << endl;
        cout << v3.getLength() << endl;

    }

    void testPolygons()
    {
        vector<Vec2Df> points;
        points.push_back(Vec2Df(0.0, 0.0));
        points.push_back(Vec2Df(1.0, 0.0));
        points.push_back(Vec2Df(1.0, 1.0));
        points.push_back(Vec2Df(0.5, 0.1));
        points.push_back(Vec2Df(0.0, 1.0));

        Polygon2D poly(points);

        bool failed = false;

        Vec2Df p1(0.5, 0.05);
        if (!poly.contains(p1))
        {
            cout << "Polygon should contain " << p1 << endl;
            failed = true;
        }

        Vec2Df p2(1.1, 0.1);
        if (poly.contains(p2))
        {
            cout << "Polygon should not contain " << p2 << endl;
            failed = true;
        }

        if (!failed)
        {
            cout << "Polygon : All containment tests passed." << endl;
        }

        vector<Polygon2D> polys = poly.offset(0.5);

        if (polys.size() != 1)
        {
            cout << "Polygon : failed growth." << endl;
        }
        else
        {
            const Polygon2D& bigPoly = polys[0];
            cout << "BigPoly : ";
            for (unsigned int i = 0; i < bigPoly.getPoints().size(); i++)
            {
                if (i > 0)
                {
                    cout << ", ";
                }

                cout << bigPoly.getPoints()[i];
            }
            cout << endl;
        }

        polys = poly.offset(-0.2);

        for (unsigned int j = 0; j < polys.size(); j++)
        {
            const Polygon2D& shrankPoly = polys[j];
            cout << "ShrankPoly : ";
            for (unsigned int i = 0; i < shrankPoly.getPoints().size(); i++)
            {
                if (i > 0)
                {
                    cout << ", ";
                }

                cout << shrankPoly.getPoints()[i];
            }
            cout << endl;
        }
    }
}
