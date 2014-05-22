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

#include <cstdlib>
#include <iostream>
#include <vector>

#include "tests/event.h"
#include "tests/ecs.h"
#include "tests/geometry.h"
#include "tests/random.h"
#include "tests/graph.h"
#include "tests/threading.h"
#include "tests/render.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

int main()
{
    RenderTest::testThread();

    EventTest::testEvents();
    EcsTest::testEcs();
    GeometryTest::testVectors();
    RandomTest::testNumberGenerator();
    GraphTest::testPlanarGraph();
    ThreadingTest::testChannel();

    return 0;
}
