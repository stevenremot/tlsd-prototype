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

#ifndef WORLD_GENERATION_CITY_ROAD_UTIL_H
#define WORLD_GENERATION_CITY_ROAD_UTIL_H

#include "RoadQuery.h"
#include "../../../Graph/PlanarGraph.h"
#include "../../../Geometry/Vec2D.h"

namespace World
{
    namespace Generation
    {
        namespace City
        {
            /**
             * Return the intersection between a road query and a graph edge.
             *
             * @param[in] query
             * @param[in] e2
             * @param[out] v
             *
             * @return true if there is an intersection, false otherwise
             */
            bool getIntersection(
                const RoadQuery& query,
                const Graph::PlanarEdge& e2,
                Geometry::Vec2Df& v
            );

            /**
             * Return the nearest intersection between a road query and a graph's edges
             *
             * @param[in] query
             * @param[in] graph
             * @param [out] nearestIntersection
             * @param [out] intersectedEdge
             *
             * @return true if there was an intersection between the query and the
             *              graph, false otherwise
             */
            bool getNearestIntersection(
                RoadQuery& query,
                const Graph::PlanarGraph& graph,
                Geometry::Vec2Df& nearestIntersection,
                Graph::PlanarEdge& intersectedEdge
            );

            /**
             * Project the position on the edge if possible
             *
             * @param[in] position
             * @param[in] edge
             * @param[out] projection
             *
             * @return true if a projection was possible, false otherwise
             */
            Geometry::Vec2Df getProjection(
                const Geometry::Vec2Df& position,
                const Graph::PlanarEdge& edge
            );

            bool getNearestProjection(
                RoadQuery& query,
                const Graph::PlanarGraph& graph,
                Geometry::Vec2Df& nearestProjection,
                Graph::PlanarEdge& projectionEdge
            );
        }
    }
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
