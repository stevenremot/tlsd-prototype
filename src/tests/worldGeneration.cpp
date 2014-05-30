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

#include "worldGeneration.h"

#include <iostream>
#include <cmath>

#include "../World/Generation/City/RoadExpander.h"
#include "../World/Generation/City/IntersectionConstraint.h"
#include "../World/Generation/City/NeighbourNodeConstraint.h"
#include "../World/Generation/City/NeighbourEdgeConstraint.h"
#include "../World/Generation/City/MergeConstraint.h"
#include "../World/Generation/City/LotCreation.h"
#include "../Graph/PlanarGraph.h"
#include "../Graph/PlanarPrimitiveExtraction.h"
#include "SvgDrawer.h"

using World::Generation::City::RoadExpander;
using World::Generation::City::QueryCreator;
using World::Generation::City::BranchRequest;
using World::RoadNetwork;
using Graph::PlanarGraph;
using Graph::PlanarNode;
using Graph::PlanarEdge;
using Geometry::Vec2Df;
using Graphics::Color;
using std::cout;
using std::endl;

namespace WorldGenerationTests
{
    void testRoadExpansion()
    {
        PlanarGraph graph;
        PlanarNode n1 = graph.addNode(Vec2Df(0.0, 0.0));
        PlanarNode n2 = graph.addNode(Vec2Df(30.0, 0.0));
        PlanarEdge e = graph.addEdge(n1, n2);

        Random::NumberGenerator gen(42);

        RoadExpander expander(QueryCreator(45.0, 0.25, gen), RoadNetwork(graph, 0.1, Color(1.0, 1.0, 1.0)));
        expander.addRoadConstraint(new World::Generation::City::NeighbourNodeConstraint(30));
        expander.addRoadConstraint(new World::Generation::City::NeighbourEdgeConstraint(30));
        expander.addRoadConstraint(new World::Generation::City::IntersectionConstraint(15));
        expander.addRoadConstraint(new World::Generation::City::MergeConstraint(15, 0.3));


        expander.addBranchRequest(BranchRequest(n2, e));

        Test::SvgDrawer svg(1000, 1000);

        for (unsigned int i = 0; i < 200; i++)
        {
            expander.expand();
        }

        const PlanarGraph& newGraph = expander.getRoadNetwork().getGraph();

        svg.drawGraph(newGraph);

        svg.end();

        cout << svg.getContent().str();
    }

    void testLotCreation()
    {
        // +------+
        // |      /
        // |      \
        // +------+

        std::vector<Vec2Df> points;
        points.push_back(Vec2Df(0, 0));
        points.push_back(Vec2Df(100, 0));
        points.push_back(Vec2Df(75, 50));
        points.push_back(Vec2Df(100, 100));
        points.push_back(Vec2Df(0, 100));

        Geometry::Polygon2D poly(points);

        Random::NumberGenerator rng(42);

        World::Generation::City::LotCollection lots =
            World::Generation::City::createLots(
                poly,
                10,
                30,
                rng
            );

        const char* colors[] = {"red", "green", "blue"};

        Test::SvgDrawer svg(200, 200);

        for (unsigned int i = 0; i < lots.size(); i++)
        {
            const Geometry::Polygon2D& lot = lots[i];
            const std::vector<Vec2Df>&  points = lot.getPoints();

            for (unsigned int j = 0; j < points.size(); j++)
            {
                const Vec2Df& p1 = points[j];
                const Vec2Df& p2 = points[(j + 1) % points.size()];

                svg.drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY(), colors[i % 3]);
            }
        }

        svg.end();

        cout << svg.getContent().str();
    }
}
