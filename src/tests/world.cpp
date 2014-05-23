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

#include "world.h"

#include <iostream>

#include "../World/RoadNetwork.h"

using std::cout;
using std::endl;
using Graph::PlanarGraph;
using Graph::PlanarNode;
using World::RoadNetwork;
using Geometry::Vec2Df;
using std::vector;

namespace WorldTest
{
    void testRoadNetworkModel()
    {
        PlanarGraph graph;
        const PlanarNode& n1 = graph.addNode(Vec2Df(0.0, 0.0));
        const PlanarNode& n2 = graph.addNode(Vec2Df(1.0, 0.0));
        const PlanarNode& n3 = graph.addNode(Vec2Df(0.0, 1.0));
        const PlanarNode& n4 = graph.addNode(Vec2Df(-1.0, -1.0));

        graph.addEdge(n1, n2);
        graph.addEdge(n1, n3);
        graph.addEdge(n1, n4);

        RoadNetwork road(graph, 0.1, Graphics::Color(1.0, 1.0, 1.0));
        const Graphics::Render::Model3D& model = road.getModel();

        // Vertex display
        const vector<Geometry::Vec3Df>& vertices = model.getVertices();
        cout << "Vertices : " << endl;
        for (unsigned int i = 0; i < vertices.size(); i++)
        {
            cout << i << " : " << vertices[i] << endl;
        }

        const vector<Graphics::Render::Face>& faces = model.getFaces();
        cout << "Faces : " << endl;
        for (unsigned int i = 0; i < faces.size(); i++)
        {
            Graphics::Render::Face face = faces[i];
            cout << "Face : (";
            for (unsigned int j = 0; j < 3; j++)
            {
                cout << face[j];
                if (j < 2)
                {
                    cout << ", ";
                }
            }
            cout << ")" << endl;
        }

    }
}
