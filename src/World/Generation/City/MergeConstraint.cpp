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

#include "MergeConstraint.h"

#include <cmath>

#include "RoadUtil.h"
#include "../../../Geometry/Vec2D.h"

using Geometry::Vec2Df;
using Graph::PlanarGraph;
using Graph::PlanarNode;
using Graph::PlanarEdge;

namespace World
{
    namespace Generation
    {
        namespace City
        {
            bool isSimilar(
                const RoadQuery& query,
                const PlanarEdge& edge,
                float radius,
                float deviation
            ) {
                const Vec2Df& origin = query.getOriginNode().getPosition();
                const Vec2Df direction = Vec2Df::fromPolar(
                    query.getOrientation(),
                    query.getLength()
                );
                const Vec2Df end = origin + direction;

                const Vec2Df& n1 = edge.getFirstNode().getPosition();
                const Vec2Df& n2 = edge.getSecondNode().getPosition();

                if ((origin - getProjection(origin, n1, n2)).getLength() <= radius ||
                    (end - getProjection(end, n1, n2)).getLength() <= radius ||
                    (n1 - getProjection(n1, origin, end)).getLength() <= radius ||
                    (n2 - getProjection(n2, origin, end)).getLength() <= radius)
                {
                    const Vec2Df d = edge.getDirection().normalize();
                    const Vec2Df normalDirection = direction.normalize();
                    if (normalDirection.dot(d) > deviation)
                    {
                        return true;
                    }
                }

                return false;
            }

            void MergeConstraint::insert(
                    RoadQuery& query,
                    const RoadNetwork& network
            ) {
                const PlanarGraph& graph = network.getGraph();

                const PlanarGraph::EdgeCollection& edges = graph.getEdges();
                for (unsigned int i = 0; i < edges.size(); i++)
                {
                    const PlanarEdge& edge = edges[i];
                    if (isSimilar(query, edge, radius_, deviation_))
                    {
                        query.setState(RoadQuery::CancelledState);
                        return;
                    }
                }
            }
        }
    }
}
