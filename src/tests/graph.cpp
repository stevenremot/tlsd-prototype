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

#include "../Graph/PlanarGraph.h"

using std::cout;
using std::endl;

using Graph::PlanarGraph;
using Graph::PlanarNode;
using Graph::PlanarEdge;

using Geometry::Vec2Df;

namespace GraphTest
{
    void testPlanarGraph()
    {
        PlanarGraph g;
        PlanarNode& n1 = g.addNode(Vec2Df(0, 0));
        PlanarNode& n2 = g.addNode(Vec2Df(2, 2));
        PlanarNode& n3 = g.addNode(Vec2Df(0, 1));

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

        cout << "n1 before remove" << endl;
        PlanarGraph::EdgeCollection edges = g.getNeighbourEdges(n1);
        for (unsigned int i = 0; i < edges.size(); i++)
        {
            PlanarEdge& edge = edges[i];
            const PlanarNode& otherNode = edge.getOtherNode(n1);
            cout << "Neighbour : " << otherNode.getPosition() << endl;
        }

        cout << endl;

        g.removeEdge(edgeToRemove);

        cout << "n1 after removing (n1, n2)" << endl;
        edges = g.getNeighbourEdges(n1);
        for (unsigned int i = 0; i < edges.size(); i++)
        {
            PlanarEdge& edge = edges[i];
            const PlanarNode& otherNode = edge.getOtherNode(n1);
            cout << "Neighbour : " << otherNode.getPosition() << endl;
        }
        cout << endl;

        g.addEdge(n1, n2);

        g.removeNode(n3);

        cout << "n1 after removing n3" << endl;
        edges = g.getNeighbourEdges(n1);
        for (unsigned int i = 0; i < edges.size(); i++)
        {
            PlanarEdge& edge = edges[i];
            const PlanarNode& otherNode = edge.getOtherNode(n1);
            cout << "Neighbour : " << otherNode.getPosition() << endl;
        }
    }
}
