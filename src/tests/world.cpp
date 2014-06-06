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
#include "../World/GroundCoefficients.h"
#include "../World/BiomeMap.h"
#include "../World/World.h"
#include "../Geometry/Vec2D.h"
#include "../Geometry/Polygon2D.h"
#include "../Random/NumberGenerator.h"
#include "../World/Chunk.h"
#include "../Graphics/Render/Model3D.h"
#include "../World/Generation/CoefficientsGenerator.h"
#include "../World/Ground.h"
#include "SvgDrawer.h"

using std::cout;
using std::endl;
using Graph::PlanarGraph;
using Graph::PlanarNode;
using World::RoadNetwork;
using Geometry::Vec2Df;
using std::vector;
using World::GroundCoefficients;
using Geometry::Polygon2D;
using World::BiomeMap;
using Random::NumberGenerator;
using World::Chunk;
using Graphics::Render::Model3D;



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

    void testGroundCoefficients()
    {
        GroundCoefficients groundcoef;
        groundcoef.setCoefficient(1,0,0,-0.6);
        groundcoef.setCoefficient(2,0,0,0.1);

        float coef1 = groundcoef.getCoefficient(1,0,0);
        cout << "Coefficient from the first octave : " << coef1 << endl;

        try
        {
            groundcoef.getCoefficient(2,2,0);
            cout << "GCoef : should not succeed" << endl;
        }
        catch(const GroundCoefficients::BadParametersException& e)
        {
            cout << "GCoef : exception successfully thrown" << endl;
        }
    }


    void testGroundModel()
    {
        BiomeMap biomeMap;
        World::World world;
        NumberGenerator rng(1);
        /*vector<Vec2Df> points;
        points.push_back(Vec2Df(0.0, 0.0));
        points.push_back(Vec2Df(512.0, 0.0));
        points.push_back(Vec2Df(512.0, 512.0));
        points.push_back(Vec2Df(0.0, 512.0));

        Polygon2D poly(points);
        biomeMap.addCityPolygon(poly);*/
        for (unsigned int i = 0; i < 25; i++)
        {
        biomeMap.setPerlinCoef(i/5,i%5,World::Generation::generatePerlinCoefficient(rng));
        }
        world.setBiomeMap(biomeMap);
        for (unsigned int i = 0; i<25; i++)
        {
            Chunk chunk;
            chunk.setState(Chunk::PreparedState);
            chunk.setCoefficients(World::Generation::generateGroundCoefficients(rng));
            if (i==6 || i==7 || i==8 || i==11 || i==12 || i==13 || i==16 || i==17 || i==18)
            {
                chunk.setState(Chunk::GeneratedState);
            }
            world.setChunk(i/5,i%5,chunk);
        }
        // Model3D model11 = World::computeGroundModel(world, 1, 1);
        // Model3D model21 = World::computeGroundModel(world, 2, 1);
        // Model3D model31 = World::computeGroundModel(world, 3, 1);
        // Model3D model12 = World::computeGroundModel(world, 1, 2);
        Model3D model22 = World::computeGroundModel(world, 2, 2);
        // Model3D model32 = World::computeGroundModel(world, 3, 2);
        // Model3D model13 = World::computeGroundModel(world, 1, 3);
        // Model3D model23 = World::computeGroundModel(world, 2, 3);
        // Model3D model33 = World::computeGroundModel(world, 3, 3);

        Test::SvgDrawer svg(128, 512);

        for (unsigned int i = 0; i < model22.getVertices().size(); i++)
        {
            const Geometry::Vec3Df& vertex = model22.getVertices()[i];

            if (vertex.getX() < 128 && vertex.getY() < 128)
            {
                svg.drawCircle(vertex.getX() - 64, vertex.getZ() - 256, 1, "red");
            }
        }

        svg.end();

        std::cout << svg.getContent().str();
    }
}
