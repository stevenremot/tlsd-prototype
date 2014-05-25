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

#include "NeighbourNodeConstraint.h"

#include "../../../Geometry/Vec2D.h"
#include "RoadUtil.h"
#include "EndNodeQueryInserter.h"

using Geometry::Vec2Df;
using Graph::PlanarNode;
using Graph::PlanarEdge;
using Graph::PlanarGraph;

namespace World
{
    namespace Generation
    {
        namespace City
        {
            bool hasExistingEdge(
                const PlanarNode& n1,
                const PlanarNode& n2,
                const PlanarGraph& graph
            ) {
                const PlanarGraph::EdgeCollection& edges = graph.getEdges();
                for (unsigned int i = 0; i < edges.size(); i++)
                {
                    const PlanarEdge& edge = edges[i];
                    if (edge.hasNode(n1) && edge.hasNode(n2))
                    {
                        return true;
                    }
                }
                return false;
            }

            bool getNearestNode(
                const PlanarNode& originNode,
                const PlanarGraph& graph,
                float radius,
                PlanarNode& nearestNode
            ) {
                const PlanarGraph::NodeCollection& nodes = graph.getNodes();
                const Vec2Df& origin = originNode.getPosition();
                float distance = 0;
                bool gotNearest = false;

                for (unsigned int i = 0; i < nodes.size(); i++)
                {
                    const PlanarNode& node = nodes[i];
                    const Vec2Df& position = node.getPosition();
                    Vec2Df direction = position - origin;
                    float currentDistance = direction.getLength();

                    Vec2Df intersection;
                    PlanarEdge intersectedEdge;
                    RoadQuery query = RoadQuery(
                        originNode,
                        direction.getOrientation(),
                        currentDistance
                    );

                    if (node == originNode ||
                        currentDistance > radius ||
                        hasExistingEdge(originNode, node, graph) ||
                        getNearestIntersection(
                            query,
                            graph,
                            intersection,
                            intersectedEdge
                        ))
                    {
                        continue;
                    }

                    if (!gotNearest || currentDistance < distance)
                    {
                        gotNearest = true;
                        distance = currentDistance;
                        nearestNode = node;
                    }
                }

                return gotNearest;
            }

            void NeighbourNodeConstraint::insert(
                RoadQuery& query,
                const RoadNetwork& network
            ) {
                if (query.getState() == RoadQuery::PendingState)
                {
                    PlanarNode nearestNode;

                    if (getNearestNode(
                            query.getOriginNode(),
                            network.getGraph(),
                            radius_,
                            nearestNode
                        ))
                    {
                        query.setState(RoadQuery::DoneState);
                        query.setInserter(new EndNodeQueryInserter(nearestNode));
                        Vec2Df direction =
                            nearestNode.getPosition() - query.getOriginNode().getPosition();
                        query.setOrientation(direction.getOrientation());
                        query.setLength(direction.getLength());
                    }
                }
            }
        }
    }
}
