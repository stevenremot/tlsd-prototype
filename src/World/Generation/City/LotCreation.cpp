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

#include "LotCreation.h"

#include <map>
#include <cmath>

#include "GraphSpliter.h"
#include "../../../Graph/PlanarPrimitiveExtraction.h"

using std::map;
using std::vector;
using Graph::PlanarPrimitive;
using Graph::PlanarGraph;
using Graph::PlanarEdge;
using Graph::PlanarNode;
using Geometry::Vec2Df;

namespace World
{
    namespace Generation
    {
        namespace City
        {
            bool isRoadEdge(
                const map<PlanarEdge, bool>& isRoad,
                const PlanarEdge& edge
            ) {
                return isRoad.find(edge) != isRoad.end() && isRoad.at(edge);
            }

            bool getEdgeToSplit(
                const PlanarGraph& graph,
                const map<PlanarEdge, bool>& isRoad,
                float maximumRoadLength,
                PlanarEdge& edge
            ) {
                float longestLength = 0;
                bool gotEdge = false;

                PlanarGraph::EdgeCollection edges = graph.getEdges();

                for (unsigned int i = 0; i < edges.size(); i++)
                {
                    const PlanarEdge& currentEdge = edges[i];
                    const float length = currentEdge.getDirection().getLength();

                    if ((length >= maximumRoadLength &&
                         (!gotEdge ||
                          (length > longestLength &&
                           (isRoadEdge(isRoad, currentEdge) || !isRoadEdge(isRoad, edge))) ||
                          (isRoadEdge(isRoad, currentEdge) && ! isRoadEdge(isRoad, edge)))))
                    {
                        gotEdge = true;
                        longestLength = length;
                        edge = currentEdge;
                    }
                }

                return gotEdge;
            }


            LotCollection createLots(
                const PlanarPrimitive& cycle,
                map<PlanarEdge, bool>& isRoad,
                float minimumRoadLength,
                float maximumRoadLength,
                Random::NumberGenerator& rng
            ) {
                if (cycle.getType() != PlanarPrimitive::CycleType)
                {
                    throw WrongPrimitiveException();
                }

                PlanarGraph graph = cycle.convertToGraph();
                LotCollection lots;

                PlanarEdge edgeToSplit;

                if (getEdgeToSplit(graph, isRoad, maximumRoadLength, edgeToSplit))
                {
                    const Vec2Df splitDirection = edgeToSplit.getDirection();
                    const float splitSize =
                        minimumRoadLength + rng.getUniform(
                            0,
                            splitDirection.getLength() - 2.0 * minimumRoadLength
                        );

                    const Vec2Df splitPoint =
                        edgeToSplit.getFirstNode().getPosition() +
                        (splitDirection.normalize() * splitSize);

                    const Vec2Df splitNormal = splitDirection.normalize().getOrthogonal();

                    GraphSpliter spliter(splitPoint, splitNormal);
                    spliter.splitGraph(graph, isRoad);

                    Graph::PlanarPrimitiveCollection primitives =
                        Graph::extractPrimitives(graph);

                    for (unsigned int i = 0; i < primitives.size(); i++)
                    {
                        const PlanarPrimitive& prim = primitives[i];
                        if (prim.getType() == PlanarPrimitive::CycleType)
                        {
                            const LotCollection& newLots = createLots(
                                prim,
                                isRoad,
                                minimumRoadLength,
                                maximumRoadLength,
                                rng
                            );
                            lots.insert(lots.end(), newLots.begin(), newLots.end());
                        }
                    }
                }
                else
                {
                    // Check if the cycle has edges near road
                    bool isNearRoad = false;

                    const PlanarGraph::EdgeCollection& edges = graph.getEdges();
                    for (unsigned int i = 0; i < edges.size(); i++)
                    {
                        if (isRoadEdge(isRoad, edges[i]))
                        {
                            isNearRoad = true;
                            break;
                        }
                    }

                    if (isNearRoad)
                    {
                        std::vector<Vec2Df> points;
                        const PlanarGraph::NodeCollection& nodes = graph.getNodes();

                        for (unsigned int i = 0; i < nodes.size(); i++)
                        {
                            points.push_back(nodes[i].getPosition());
                        }

                        lots.push_back(Geometry::Polygon2D(points));
                    }
                }

                return lots;
            }

            LotCollection createLots(
                const PlanarPrimitive& cycle,
                float minimumRoadLength,
                float maximumRoadLength,
                Random::NumberGenerator& rng
            ) {
                map<PlanarEdge, bool> isRoad;

                const PlanarGraph::EdgeCollection edges = cycle.getEdges();
                for (unsigned int i = 0; i < edges.size(); i++)
                {
                    isRoad[edges[i]] = true;
                }

                return createLots(
                    cycle,
                    isRoad,
                    minimumRoadLength,
                    maximumRoadLength,
                    rng
                );
            }
        }
    }
}
