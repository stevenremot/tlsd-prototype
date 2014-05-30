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

#ifndef WORLD_GENERATION_CITY_GRAPH_SPLITER_H
#define WORLD_GENERATION_CITY_GRAPH_SPLITER_H

#include <map>

#include "../../../Geometry/Vec2D.h"
#include "../../../Graph/PlanarGraph.h"

namespace World
{
    namespace Generation
    {
        namespace City
        {
            /**
             * A class that can split a graph along a direction.
             *
             * Used for lot creation
             */
            class GraphSpliter
            {
            public:

                struct SplitInformation {
                    SplitInformation(const Graph::PlanarEdge& edge,
                                     const Geometry::Vec2Df& point):
                        edge(edge),
                        point(point)
                    {}

                    Graph::PlanarEdge edge;
                    Geometry::Vec2Df point;
                };

                GraphSpliter(
                    const Geometry::Vec2Df& origin,
                    const Geometry::Vec2Df& direction
                ):
                    origin_(origin),
                    direction_(direction)
                {}

                /**
                 * Split the graph along the spliter's direction
                 *
                 * @param [inout] graph
                 * @param [inout] isRoad telling whether an edge is a road of is
                 *                        inside a lot
                 */
                void splitGraph(
                    Graph::PlanarGraph& graph,
                    std::map<Graph::PlanarEdge, bool>& isRoad
                );

                bool operator()(
                    const SplitInformation& p1,
                    const SplitInformation& p2
                );

            private:
                Geometry::Vec2Df origin_;
                Geometry::Vec2Df direction_;

                bool getSplitPoint(
                    const Geometry::Vec2Df& p1,
                    const Geometry::Vec2Df& p2,
                    Geometry::Vec2Df& splitPoint
                );
            };
        }
    }
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
