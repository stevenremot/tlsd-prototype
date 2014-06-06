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
#include "RoadUtil.h"

#include <iostream>
#include <cmath>

using Graph::PlanarEdge;
using Graph::PlanarNode;
using Graph::PlanarGraph;
using Geometry::Vec2Df;
using Geometry::Polygon2D;

namespace World
{
    namespace Generation
    {
        namespace City
        {

            bool getIntersection(
                const RoadQuery& query,
                const PlanarEdge& e2,
                Vec2Df& v
            ) {
                const Vec2Df d1 = Vec2Df::fromPolar(
                    query.getOrientation(),
                    query.getLength()
                );
                const Vec2Df d2 = e2.getDirection();
                const Vec2Df n2 = d2.getOrthogonal().normalize();

                const Vec2Df offset = e2.getFirstNode().getPosition() -
                    query.getOriginNode().getPosition();

                const float parallel = d1.dot(n2);

                if (std::abs(parallel / d1.getLength()) < 1e-6)
                {
                    return false;
                }

                const float t = offset.dot(n2) / parallel;
                if (t < 0 || t > 1)
                {
                    return false;
                }

                v = query.getOriginNode().getPosition() + d1 * t;

                const float t2 =
                    (v - e2.getFirstNode().getPosition()).dot(d2.normalize()) / d2.getLength();
                if (t2 < 0 || t2 > 1)
                {
                    return false;
                }

                return true;
            }

            bool getNearestIntersection(
                RoadQuery& query,
                const PlanarGraph& graph,
                Vec2Df& nearestIntersection,
                PlanarEdge& intersectedEdge
            ) {
                const PlanarGraph::EdgeCollection& edges = graph.getEdges();
                const Vec2Df& origin = query.getOriginNode().getPosition();

                bool intersected = false;
                float distance = 0.0;

                for (unsigned int i = 0; i < edges.size(); i++)
                {
                    const PlanarEdge& edge = edges[i];
                    if (edge.hasNode(query.getOriginNode()))
                    {
                        continue;
                    }

                    Vec2Df currentIntersection;
                    if (getIntersection(query, edge, currentIntersection))
                    {
                        float currentDistance =
                            (origin - currentIntersection).getLength();

                        if (!intersected || currentDistance < distance) {
                            intersected = true;
                            nearestIntersection = currentIntersection;
                            distance = currentDistance;
                            intersectedEdge = edge;
                        }
                    }
                }

                return intersected;
            }

            Vec2Df getProjection(
                const Vec2Df& position,
                const Vec2Df& e1,
                const Vec2Df& e2
            ) {
                const Vec2Df edgeDirection = (e2 - e1).normalize();
                const Vec2Df edgeNormal = edgeDirection.getOrthogonal();
                const Vec2Df offset = position - e1;
                const Vec2Df projection = e1 + (offset - (edgeNormal * (edgeNormal.dot(offset))));
                const float t = edgeDirection.dot(offset) / (e2 - e1).getLength();

                if (t < 0)
                {
                    return e1;
                }
                else if (t > 1)
                {
                    return e2;
                }

                return projection;
            }

            Vec2Df getProjection(const Vec2Df& position, const PlanarEdge& edge)
            {
                return getProjection(
                    position,
                    edge.getFirstNode().getPosition(),
                    edge.getSecondNode().getPosition()
                );
            }

            bool getNearestProjection(
                RoadQuery& query,
                const PlanarGraph& graph,
                Vec2Df& nearestProjection,
                PlanarEdge& projectionEdge
            ) {
                float distance = 0;
                bool gotProjection = false;
                const Vec2Df& origin = query.getOriginNode().getPosition();
                const Vec2Df direction = Vec2Df::fromPolar(
                    query.getOrientation(),
                    query.getLength()
                );
                const Vec2Df end = origin + direction;

                const PlanarGraph::EdgeCollection& edges = graph.getEdges();
                for (unsigned int i = 0; i < edges.size(); i++)
                {
                    const PlanarEdge& edge = edges[i];
                    if (!edge.hasNode(query.getOriginNode()))
                    {
                        Vec2Df projection = getProjection(end, edge);
                        Vec2Df offset = projection - origin;
                        float currentDistance = offset.getLength();
                        RoadQuery q(
                            query.getOriginNode(),
                            offset.getOrientation(),
                            offset.getLength()
                        );
                        Vec2Df intersection;
                        PlanarEdge intersectionEdge;

                        if ((!gotProjection ||
                             currentDistance < distance) &&
                            !getNearestIntersection(
                                q,
                                graph,
                                intersection,
                                intersectionEdge
                            ))
                        {
                            gotProjection = true;
                            distance = currentDistance;
                            nearestProjection = projection;
                            projectionEdge = edge;
                        }
                    }
                }

                return gotProjection;
            }

            PlanarGraph convertToGraph(const Polygon2D& poly)
            {
                PlanarGraph graph;

                const std::vector<Vec2Df>& points = poly.getPoints();
                for(unsigned int i = 0; i < points.size(); i++)
                {
                    graph.addNode(points[i]);
                }

                const PlanarGraph::NodeCollection& nodes = graph.getNodes();
                for (unsigned int i = 0; i < nodes.size(); i++)
                {
                    const PlanarNode& n1 = nodes[i];
                    const PlanarNode& n2 = nodes[(i + 1) % nodes.size()];
                    graph.addEdge(n1, n2);
                }

                return graph;
            }


            PlanarGraph convertToGraph(const Graph::PlanarPrimitive& prim)
            {
                return PlanarGraph(prim.getNodes(), prim.getEdges());
            }

            Polygon2D convertToPolygon(const Graph::PlanarPrimitive& prim)
            {
                std::vector<Vec2Df> points;

                const PlanarGraph::NodeCollection& nodes = prim.getNodes();
                for (unsigned int i = 0; i < nodes.size(); i++)
                {
                    points.push_back(nodes[i].getPosition());
                }

                return Polygon2D(points);
            }
        }
    }
}
