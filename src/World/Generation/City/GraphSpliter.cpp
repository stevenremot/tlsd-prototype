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

#include "GraphSpliter.h"

#include <algorithm>

using std::map;
using Geometry::Vec2Df;
using Graph::PlanarGraph;
using Graph::PlanarEdge;
using Graph::PlanarNode;

namespace World
{
    namespace Generation
    {
        namespace City
        {
            bool GraphSpliter::getSplitPoint(
                const Vec2Df& p1,
                const Vec2Df& p2,
                Vec2Df& splitPoint
            ) {
                const Vec2Df otherDirection = (p2 - p1).normalize();
                const Vec2Df otherNormal = otherDirection.getOrthogonal();

                if (std::abs(direction_.dot(otherNormal)) < 1e-6)
                {
                    return false;
                }

                const Vec2Df offset = p1 - origin_;
                const float t = offset.dot(otherNormal) / direction_.dot(otherNormal);
                splitPoint = origin_ + direction_ * t;
                const float t2 =
                    (splitPoint - p1).dot(otherDirection) / (p2 - p1).getLength();

                if (t2 < 0 || t2 > 1)
                {
                    return false;
                }

                return true;
            }

            void GraphSpliter::splitGraph(
                PlanarGraph& graph,
                map<PlanarEdge, bool>& isRoad
            ) {
                const PlanarGraph::EdgeCollection& edges = graph.getEdges();
                std::vector<SplitInformation> splits;

                for (unsigned int i = 0; i < edges.size(); i++)
                {
                    const PlanarEdge& edge = edges[i];
                    Vec2Df splitPosition;
                    if (getSplitPoint(
                            edge.getFirstNode().getPosition(),
                            edge.getSecondNode().getPosition(),
                            splitPosition
                        ))
                    {
                        splits.push_back(SplitInformation(edge, splitPosition));
                    }
                }

                std::sort(splits.begin(), splits.end(), *this);

                for (unsigned int i = 0; i < splits.size(); i+= 2)
                {
                    const SplitInformation& split1 = splits[i];
                    const SplitInformation& split2 = splits[i + 1];

                    const PlanarEdge& edge1 = split1.edge;
                    const PlanarEdge& edge2 = split2.edge;

                    const Vec2Df& point1 = split1.point;
                    const Vec2Df& point2 = split2.point;

                    const PlanarNode& node1 = graph.addNode(point1);
                    graph.removeEdge(edge1);
                    const PlanarEdge& e11 = graph.addEdge(edge1.getFirstNode(), node1);
                    const PlanarEdge& e12 = graph.addEdge(edge1.getSecondNode(), node1);
                    isRoad[e11] = isRoad[e12] =
                        isRoad.find(edge1) != isRoad.end() && isRoad.at(edge1);

                    const PlanarNode& node2 = graph.addNode(point2);
                    graph.removeEdge(edge2);
                    const PlanarEdge& e21 = graph.addEdge(edge2.getFirstNode(), node2);
                    const PlanarEdge& e22 = graph.addEdge(edge2.getSecondNode(), node2);
                    isRoad[e21] = isRoad[e22] =
                        isRoad.find(edge2) != isRoad.end() && isRoad.at(edge2);

                    graph.addEdge(node1, node2);
                }
            }

            bool GraphSpliter::operator()(
                const GraphSpliter::SplitInformation& p1,
                const GraphSpliter::SplitInformation& p2
            ) {
                return direction_.dot(p1.point) < direction_.dot(p2.point);
            }
        }
    }
}
