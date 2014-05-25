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

#include "../World/Generation/City/RoadExpander.h"
#include "../World/Generation/City/IntersectionConstraint.h"
#include "../Graph/PlanarGraph.h"

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
        PlanarNode n2 = graph.addNode(Vec2Df(1.0, 0.0));
        PlanarEdge e = graph.addEdge(n1, n2);

        Random::NumberGenerator gen;

        RoadExpander expander(QueryCreator(2.0, gen), RoadNetwork(graph, 0.1, Color(1.0, 1.0, 1.0)));
        expander.addRoadConstraint(new World::Generation::City::IntersectionConstraint(0.1));

        expander.addBranchRequest(BranchRequest(n2, e));

        cout << "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
             << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"1000\" height=\"1000\"><g transform=\"translate(500 500)\">";

        for (unsigned int i = 0; i < 200; i++)
        {
            expander.expand();
        }

        const PlanarGraph& newGraph = expander.getRoadNetwork().getGraph();

        const PlanarGraph::EdgeCollection& edges = newGraph.getEdges();
        for (unsigned int i = 0; i < edges.size(); i++)
        {
            const PlanarEdge& edge = edges[i];
            const Vec2Df& p1 = edge.getFirstNode().getPosition();
            const Vec2Df& p2 = edge.getSecondNode().getPosition();

            cout << "<line x1=\"" << p1.getX() * 10
                 << "\" y1=\"" << p1.getY() * 10
                 << "\" x2=\"" << p2.getX() * 10
                 << "\" y2=\"" << p2.getY() * 10
                 << "\" stroke=\"black\" />";
        }

        cout << "</g></svg>";
    }
}
