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

#include "tests/animation.h"
#include "tests/event.h"
#include "tests/ecs.h"
#include "tests/geometry.h"
#include "tests/random.h"
#include "tests/graph.h"
#include "tests/threading.h"
#include "tests/render.h"
#include "tests/core.h"
#include "tests/world.h"
#include "tests/worldGeneration.h"
#include "tests/physics.h"
#include "tests/input.h"
#include "Application/Application.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

int main()
{
    // EventTest::testEvents();
    // EcsTest::testEcs();
    // EcsTest::testSharedEntity();
    // CoreTest::testSharedPtr();
    // GeometryTest::testVectors();
    // GeometryTest::testPolygons();
    // RandomTest::testNumberGenerator();
    GraphTest::testPlanarGraph();
    // GraphTest::testIsBetween();
    // GraphTest::testPrimitiveExtraction();
    // GraphTest::testPlanarCopy();
    // GraphTest::testFilamentInCycleExtraction();
    // ThreadingTest::testChannel();
    // WorldTest::testRoadNetworkModel();
    // WorldGenerationTests::testRoadExpansion();
    // WorldTest::testGroundCoefficients();
    // WorldTest::testGroundModel();
    // WorldGenerationTests::testRoadExpansion();
    // WorldGenerationTests::testLotCreation();
    // WorldGenerationTests::testCityCreation();
    // AnimationTest::testAnimation();
    // RenderTest::testRenderSystem(10);
    // PhysicsTest::testMovementSystem();
    //InputTest::testPlayerSystem();
    // InputTest::testCoordinates();

    // Application::Application app;
    // app.start();

    return 0;
}
