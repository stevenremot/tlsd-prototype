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

using std::cout;
using std::endl;

namespace GeometryTest
{
    void testVectors()
    {
        Geometry::Vec2Df v1(1, 2);
        Geometry::Vec2Df v2(4, 5);

        cout << v1 + v2 << endl;
        cout << v1 - v2 << endl;
        cout << v1 * v2 << endl;
        cout << v1 * 4 << endl;
        cout << -v1 << endl;
        cout << v1.getLength() << endl;

        Geometry::Vec3Df v3(1, 2, 3);
        Geometry::Vec3Df v4(4, 5, 6);

        cout << v3 + v4 << endl;
        cout << v3 - v4 << endl;
        cout << v3 * v4 << endl;
        cout << v3 * 4 << endl;
        cout << -v3 << endl;
        cout << v3.getLength() << endl;
    }
}
