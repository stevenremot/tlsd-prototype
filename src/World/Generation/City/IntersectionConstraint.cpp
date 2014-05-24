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

#include "IntersectionConstraint.h"

#include <cmath>

#include "../../../Graph/PlanarGraph.h"
#include "EdgeSplitQueryInserter.h"

using Graph::PlanarNode;
using Graph::PlanarEdge;
using Graph::PlanarGraph;
using Geometry::Vec2Df;

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
                Vec2Df d1 = Vec2Df::fromPolar(
                    query.getOrientation(),
                    query.getLength()
                );
                Vec2Df d2 = e2.getDirection();
                Vec2Df n2 = d2.getOrthogonal().normalize();

                Vec2Df offset = e2.getFirstNode().getPosition() -
                    query.getOriginNode().getPosition();

                float parallel = d1.dot(n2);

                if (abs(parallel) < 1e-6)
                {
                    return false;
                }

                float t = offset.dot(n2) / parallel;
                if (t < 0 || t > 1)
                {
                    return false;
                }

                v = query.getOriginNode().getPosition() + d1 * t;

                float otherStep = (v - e2.getFirstNode().getPosition()).dot(d2.normalize());
                float t2 = otherStep / d2.getLength();
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

            void IntersectionConstraint::insert(
                RoadQuery& query,
                const RoadNetwork& network
            ) {
                if (query.getState() != RoadQuery::CancelledState)
                {
                    Vec2Df intersection;
                    PlanarEdge intersectedEdge;
                    const Vec2Df& origin = query.getOriginNode().getPosition();

                    if (getNearestIntersection(
                            query,
                            network.getGraph(),
                            intersection,
                            intersectedEdge
                        ))
                    {
                        float length = (origin - intersection).getLength();
                        if (length < minimalLength_)
                        {
                            query.setState(RoadQuery::CancelledState);
                        }
                        else if (query.getState() != RoadQuery::DoneState)
                        {
                            query.setLength(length);
                            query.setInserter(new EdgeSplitQueryInserter(
                                                   intersectedEdge,
                                                   intersection
                                               ));
                        }
                    }
                }
            }
        }
    }
}
