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

#include "graph.h"

#include <iostream>
#include <vector>
#include <string>

#include "../Graph/PlanarGraph.h"
#include "../Graph/PlanarUtil.h"
#include "../Graph/PlanarPrimitiveExtraction.h"
#include "SvgDrawer.h"

using std::cout;
using std::endl;
using std::vector;

using Graph::PlanarGraph;
using Graph::PlanarNode;
using Graph::PlanarEdge;
using Graph::isBetween;
using Graph::PlanarPrimitive;

using Geometry::Vec2Df;

namespace GraphTest
{
    void testPlanarGraph()
    {
        PlanarGraph g;
        PlanarNode n1 = g.addNode(Vec2Df(0, 0));
        PlanarNode n2 = g.addNode(Vec2Df(2, 2));
        PlanarNode n3 = g.addNode(Vec2Df(0, 1));

        // Test duplicate :
        g.addNode(Vec2Df(0, 1));
        if (g.getNodes().size() > 3)
        {
            cout << "Bad size : " << g.getNodes().size() << endl;
        }

        PlanarEdge edgeToRemove = g.addEdge(n1, n2);
        g.addEdge(n2, n3);
        g.addEdge(n3, n1);
        g.addEdge(n1, n3); // Double definition, to check this case

        cout << "n1 : " << n1.getPosition() << endl;
        cout << "n2 : " << n2.getPosition() << endl;
        cout << "n3 : " << n3.getPosition() << endl;
        cout << endl;

        cout << "n2 before remove" << endl;
        PlanarGraph::EdgeCollection edges = g.getNeighbourEdges(n2);
        for (unsigned int i = 0; i < edges.size(); i++)
        {
            PlanarEdge& edge = edges[i];
            const PlanarNode& otherNode = edge.getOtherNode(n2);
            cout << "Neighbour : " << otherNode.getPosition() << endl;
        }

        cout << endl;

        g.removeEdge(edgeToRemove);

        cout << "n2 after removing (n1, n2)" << endl;
        edges = g.getNeighbourEdges(n2);
        for (unsigned int i = 0; i < edges.size(); i++)
        {
            PlanarEdge& edge = edges[i];
            const PlanarNode& otherNode = edge.getOtherNode(n2);
            cout << "Neighbour : " << otherNode.getPosition() << endl;
        }
        cout << endl;

        g.addEdge(n1, n2);

        g.removeNode(n3);

        cout << "n2 after removing n3" << endl;
        edges = g.getNeighbourEdges(n2);
        for (unsigned int i = 0; i < edges.size(); i++)
        {
            PlanarEdge& edge = edges[i];
            const PlanarNode& otherNode = edge.getOtherNode(n2);
            cout << "Neighbour : " << otherNode.getPosition() << endl;
        }
    }

    void testIsBetween()
    {
        vector<Vec2Df> baseDirections;
        vector<Vec2Df> nextDirections;
        vector<Vec2Df> consideredDirections;
        vector<Graph::Direction> trueDirections;

        baseDirections.push_back(Vec2Df(1, 0));
        nextDirections.push_back(Vec2Df(1, 1));
        consideredDirections.push_back(Vec2Df(1, 0));
        trueDirections.push_back(Graph::ClockwiseDirection);

        baseDirections.push_back(Vec2Df(1, 0));
        nextDirections.push_back(Vec2Df(1, 1));
        consideredDirections.push_back(Vec2Df(0, 1));
        trueDirections.push_back(Graph::CounterClockwiseDirection);

        baseDirections.push_back(Vec2Df(1, 0));
        nextDirections.push_back(Vec2Df(1, 0));
        consideredDirections.push_back(Vec2Df(1, 1));
        trueDirections.push_back(Graph::CounterClockwiseDirection);

        baseDirections.push_back(Vec2Df(1, 0));
        nextDirections.push_back(Vec2Df(1, 0));
        consideredDirections.push_back(Vec2Df(1, -1));
        trueDirections.push_back(Graph::ClockwiseDirection);

        bool failed = false;

        for (unsigned int i = 0; i < baseDirections.size(); i++)
        {
            Graph::Direction falseDirection;
            if (trueDirections[i] == Graph::ClockwiseDirection)
                falseDirection = Graph::CounterClockwiseDirection;
            else
                falseDirection = Graph::ClockwiseDirection;

            if (!isBetween(baseDirections[i],
                           nextDirections[i],
                           consideredDirections[i],
                           trueDirections[i]))
            {
                cout << "isBetween : Error with data set " << i << " at truth test." << endl;
                failed = true;
            }

            if (isBetween(baseDirections[i],
                          nextDirections[i],
                          consideredDirections[i],
                          falseDirection))
            {
                cout << "isBetween : Error with data set " << i << " at false test." << endl;
                failed = true;
            }
        }

        if (!failed)
        {
            cout << "isBetween : All tests passed." << endl;
        }
    }

    void testPlanarCopy()
    {

        // +----+
        // |    |
        // |    |
        // +----+
        // |    |
        // |    |
        // +----+----+

        PlanarGraph graph;

        PlanarNode n1 = graph.addNode(Vec2Df(0, 0));
        PlanarNode n2 = graph.addNode(Vec2Df(1, 0));
        PlanarNode n3 = graph.addNode(Vec2Df(1, 1));
        PlanarNode n4 = graph.addNode(Vec2Df(1, 2));
        PlanarNode n5 = graph.addNode(Vec2Df(0, 2));
        PlanarNode n6 = graph.addNode(Vec2Df(0, 1));
        PlanarNode n7 = graph.addNode(Vec2Df(2, 0));

        graph.addEdge(n1, n2);
        graph.addEdge(n2, n3);
        graph.addEdge(n3, n4);
        graph.addEdge(n4, n5);
        graph.addEdge(n5, n6);
        graph.addEdge(n6, n1);
        graph.addEdge(n3, n6);
        graph.addEdge(n2, n7);

        PlanarGraph g2(graph);
        g2.removeEdge(g2.getEdges()[0]);
        g2.removeNode(g2.getNodes()[0]);

        cout << "Nodes : " << g2.getNodes().size()
             << ", edges : " << g2.getEdges().size() << endl;

        cout << "Original : "
             << "Nodes : " << graph.getNodes().size()
             << ", edges : " << graph.getEdges().size() << endl;
    }

    void testPrimitiveExtraction()
    {
        // +----+
        // |    |
        // |    |
        // +----+
        // |    |
        // |    |
        // +----+----+

        PlanarGraph graph;

        PlanarNode n1 = graph.addNode(Vec2Df(0, 0));
        PlanarNode n2 = graph.addNode(Vec2Df(1, 0));
        PlanarNode n3 = graph.addNode(Vec2Df(1, 1));
        PlanarNode n4 = graph.addNode(Vec2Df(1, 2));
        PlanarNode n5 = graph.addNode(Vec2Df(0, 2));
        PlanarNode n6 = graph.addNode(Vec2Df(0, 1));
        PlanarNode n7 = graph.addNode(Vec2Df(2, 0));

        graph.addEdge(n1, n2);
        graph.addEdge(n2, n3);
        graph.addEdge(n3, n4);
        graph.addEdge(n4, n5);
        graph.addEdge(n5, n6);
        graph.addEdge(n6, n1);
        graph.addEdge(n3, n6);
        graph.addEdge(n2, n7);

        Graph::PlanarPrimitiveCollection prims =
            Graph::extractPrimitives(graph);

        cout << "Primitives : " << prims.size() << " found." << endl;

        for (unsigned int i = 0; i < prims.size(); i++)
        {
            const PlanarPrimitive& prim = prims[i];
            std::string type;

            switch (prim.getType())
            {
            case PlanarPrimitive::SingletonType:
                type = "singleton";
                break;
            case PlanarPrimitive::FilamentType:
                type = "filament";
                break;
            case PlanarPrimitive::CycleType:
                type = "cycle";
                break;
            default:
                type = "none";
                break;
            }

            cout << "type : " << type << endl;

            cout << "nodes : " << endl;

            const PlanarGraph::NodeCollection& nodes = prim.getNodes();
            for (unsigned int j = 0; j < nodes.size(); j++)
            {
                cout << "\t" << nodes[j].getPosition() << endl;
            }

            cout << endl << "edges : " << endl;
            const PlanarGraph::EdgeCollection& edges = prim.getEdges();
            for (unsigned int j = 0; j < edges.size(); j++)
            {
                cout << "\t" << edges[j].getFirstNode().getPosition()
                     << " # " << edges[j].getSecondNode().getPosition() << endl;
            }

            cout << endl;
        }
    }

    void testFilamentInCycleExtraction()
    {
        // +---------+
        // |         |
        // |         |
        // |         |
        // |    +----+
        // |         |
        // |         |
        // +---------+-----+

        PlanarGraph graph;

        PlanarNode n1 = graph.addNode(Vec2Df(0, 0));
        PlanarNode n2 = graph.addNode(Vec2Df(100, 0));
        PlanarNode n3 = graph.addNode(Vec2Df(200, 0));
        PlanarNode n4 = graph.addNode(Vec2Df(100, 100));
        PlanarNode n5 = graph.addNode(Vec2Df(50, 100));
        PlanarNode n6 = graph.addNode(Vec2Df(100, 200));
        PlanarNode n7 = graph.addNode(Vec2Df(0, 200));

        graph.addEdge(n1, n2);
        graph.addEdge(n2, n3);
        graph.addEdge(n2, n4);
        graph.addEdge(n4, n5);
        graph.addEdge(n4, n6);
        graph.addEdge(n6, n7);
        graph.addEdge(n1, n7);

        Graph::PlanarPrimitiveCollection primitives = extractPrimitives(graph);

        PlanarGraph newGraph = Graph::extractFilamentsInCycles(graph, primitives);

        Test::SvgDrawer svg(400, 400);
        svg.drawGraph(newGraph);
        svg.end();
        cout << svg.getContent().str();
    }
}
