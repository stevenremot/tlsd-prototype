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
            void MergeConstraint::insert(
                    RoadQuery& query,
                    const RoadNetwork& network
            ) {
                const Vec2Df& origin = query.getOriginNode().getPosition();
                const PlanarGraph& graph = network.getGraph();

                const PlanarGraph::NodeCollection& nodes = graph.getNodes();

                for (unsigned int i = 0; i < nodes.size(); i++)
                {
                    const PlanarNode& node = nodes[i];
                    const Vec2Df& farPosition = node.getPosition();

                    if ((origin - farPosition).getLength() <= radius_)
                    {
                        const PlanarGraph::EdgeCollection& edges =
                            graph.getNeighbourEdges(node);

                        for (unsigned int j = 0; j < edges.size(); j++)
                        {
                            const PlanarEdge& edge = edges[i];
                            Vec2Df direction =
                                edge.getOtherNode(node).getPosition() - farPosition;
                            if ((query.getOrientation() - direction.getOrientation()) <= deviation_)
                            {
                                query.setState(RoadQuery::CancelledState);
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
}
