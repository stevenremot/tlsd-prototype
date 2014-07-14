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

#include "RoadNetwork.h"

#include <vector>
#include <algorithm>

#include "../Graph/PlanarUtil.h"
#include "../Geometry/Util2D.h"

using std::vector;
using Geometry::Vec3Df;
using Geometry::Vec2Df;
using Geometry::Polygon2D;
using Graphics::Render::Face;
using Graph::PlanarGraph;
using Graph::PlanarEdge;
using Graph::PlanarNode;

namespace World
{
    void createCornersForEdge(
        const PlanarNode& node,
        const PlanarEdge& previousEdge,
        RoadNetwork& network,
        Vec2Df& leftCorner,
        Vec2Df& rightCorner
    ) {
        const PlanarGraph& graph = network.getGraph();
        const float roadSize = network.getRoadSize();
        PlanarGraph::EdgeCollection edges = graph.getNeighbourEdges(node);

        const Vec2Df& p1 = previousEdge.getOtherNode(node).getPosition();
        const Vec2Df& p2 = node.getPosition();
        const Vec2Df direction = p2 - p1;

        if (edges.size() == 1)
        {
            const Vec2Df& orthogonal = direction.getOrthogonal().normalize();

            leftCorner = p2 + orthogonal * roadSize;
            rightCorner = p2 - orthogonal * roadSize;
        }
        else
        {
            edges.erase(std::find(edges.begin(), edges.end(), previousEdge));

            PlanarEdge leftEdge, rightEdge;

            getNextEdge(
                node,
                direction,
                edges,
                Graph::CounterClockwiseDirection,
                leftEdge
            );

            getNextEdge(
                node,
                direction,
                edges,
                Graph::ClockwiseDirection,
                rightEdge
            );

            const Vec2Df leftDirection =
                leftEdge.getOtherNode(node).getPosition() - p2;

            const Vec2Df rightDirection =
                rightEdge.getOtherNode(node).getPosition() - p2;

            leftCorner = p2 + Geometry::getMedian(direction, leftDirection) * roadSize;
            rightCorner = p2 - Geometry::getMedian(direction, rightDirection) * roadSize;
        }
    }

    void RoadNetwork::updateModel()
    {
        vector<Vec3Df> vertices;
        vector<Face> faces;

        const PlanarGraph::EdgeCollection& edges = graph_.getEdges();

        unsigned int baseIndex = 0;

        // Create edges meshes
        for (unsigned int i = 0; i < edges.size(); i++)
        {
            const PlanarEdge& edge = edges[i];
            const PlanarNode& n1 = edge.getFirstNode();
            const PlanarNode& n2 = edge.getSecondNode();

            Vec2Df v1, v2, v3, v4;

            createCornersForEdge(n1, edge, *this, v1, v2);
            createCornersForEdge(n2, edge, *this, v4, v3);

            vertices.push_back(Vec3Df(v1.getX(), v1.getY(), 0));
            vertices.push_back(Vec3Df(v2.getX(), v2.getY(), 0));
            vertices.push_back(Vec3Df(v3.getX(), v3.getY(), 0));
            vertices.push_back(Vec3Df(v4.getX(), v4.getY(), 0));

            faces.push_back(Face(baseIndex, baseIndex + 2, baseIndex + 1, color_));
            faces.push_back(Face(baseIndex + 1, baseIndex + 2, baseIndex + 3, color_));

            baseIndex += 4;
        }

        // Create meshes for intersection
        const PlanarGraph::NodeCollection& nodes = graph_.getNodes();
        for (unsigned int i = 0; i < nodes.size(); i++)
        {
            const PlanarNode& node = nodes[i];
            PlanarGraph::EdgeCollection neighbourEdges =
                graph_.getNeighbourEdges(node);

            if (neighbourEdges.size() > 2)
            {
                PlanarEdge edge = neighbourEdges[0];
                for (unsigned int j = 0; j < neighbourEdges.size(); j++)
                {
                    neighbourEdges.erase(
                        std::find(
                            neighbourEdges.begin(),
                            neighbourEdges.end(),
                            edge
                        )
                    );
                    Vec2Df leftCorner, rightCorner;
                    createCornersForEdge(
                        node,
                        edge,
                        *this,
                        leftCorner,
                        rightCorner
                    );

                    vertices.push_back(
                        Vec3Df(
                            leftCorner.getX(),
                            leftCorner.getY(),
                            0
                        )
                    );

                    PlanarEdge oldEdge = edge;

                    getNextEdge(
                        node,
                        node.getPosition() -
                        edge.getOtherNode(node).getPosition(),
                        neighbourEdges,
                        Graph::ClockwiseDirection,
                        edge
                    );

                    neighbourEdges.push_back(oldEdge);
                }

                for (unsigned int index = 1; index < neighbourEdges.size() - 1; index++)
                {
                    faces.push_back(
                        Face(
                            baseIndex,
                            baseIndex + index,
                            baseIndex + index + 1,
                            color_
                        )
                    );
                }

                baseIndex += neighbourEdges.size();
            }
        }

        model_ = Graphics::Render::Model3D(vertices, faces);
    }

    Polygon2D RoadNetwork::getConvexHull() const
    {
        // TODO currently implement as a bounding box
        //      create a true convex hull

        Vec2Df min;
        Vec2Df max;

        PlanarGraph::NodeCollection nodes = graph_.getNodes();

        min = max = nodes[0].getPosition();

        for (unsigned int i = 1; i < nodes.size(); i++)
        {
            const Vec2Df& pos = nodes[i].getPosition();

            if (pos.getX() < min.getX())
            {
                min.setX(pos.getX());
            }

            if (pos.getX() > max.getX())
            {
                max.setX(pos.getX());
            }

            if (pos.getY() < min.getY())
            {
                min.setY(pos.getY());
            }

            if (pos.getY() > max.getY())
            {
                max.setY(pos.getY());
            }
        }

        std::vector<Vec2Df> points;
        points.push_back(min);
        points.push_back(Vec2Df(min.getX(), max.getY()));
        points.push_back(max);
        points.push_back(Vec2Df(max.getX(), min.getY()));

        return Polygon2D(points);
    }
}
