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

#ifndef GRAPH_PLANAR_UTIL_H
#define GRAPH_PLANAR_UTIL_H

#include "../Geometry/Vec3D.h"
#include "PlanarGraph.h"

namespace Graph
{
    enum Direction { ClockwiseDirection, CounterClockwiseDirection };

    /**
     * Return true if consideredDirection is between baseDirection and nextDirection
     *
     * Everything here is based around a single point.
     *
     * @param baseDirection the origin direction, a vector coming to the
     *                      current point
     * @param nextDirection the current planed direction, a vector starting from
     *                      the current point
     * @param consideredDirection another vector starting from the current point
     * @param clockwise if set to ClockwiseDirection, return true if
     *                  consideredDirection if between base and next in a clockwise
     *                  manner
     */
    bool isBetween(const Geometry::Vec2Df& baseDirection,
                   const Geometry::Vec2Df& nextDirection,
                   const Geometry::Vec2Df& consideredDirection,
                   Direction clockwise);

    /**
     * Return the next edge to visit in the graph.
     *
     * @param[in] commonNode the node whose edges are to be considered
     * @param[in] baseDirection the direction we "come from"
     * @param[in] edges edges to consider
     * @param[in] clockwise the walking direction.
     *                      when clockwise, the right-most edge is choosen
     * @param[out] edge the variable that will get the result
     *
     * @return true if there was edges to consider, false otherwise
     */
    bool getNextEdge(const PlanarNode& commonNode,
                     const Geometry::Vec2Df& baseDirection,
                     const PlanarGraph::EdgeCollection& edges,
                     Direction clockwise,
                     PlanarEdge& edge);

    /**
     * Return the first node to use for a graph walk.
     */
    const PlanarNode& getFirstNode(const PlanarGraph& graph);
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
