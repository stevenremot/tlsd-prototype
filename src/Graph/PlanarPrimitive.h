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

#ifndef GRAPH_PLANAR_PRIMITIVE_H
#define GRAPH_PLANAR_PRIMITIVE_H

#include "PlanarGraph.h"

namespace Graph
{
    /**
     * Represents a primitive in a graph.
     *
     * Either a singleton (a single node), a filament, or a cycle.
     */
    class PlanarPrimitive
    {
    public:
        enum Type { SingletonType, FilamentType, CycleType };

        PlanarPrimitive(
            Type type,
            const PlanarGraph::NodeCollection& nodes,
            const PlanarGraph::EdgeCollection& edges
        ):
            type_(type),
            nodes_(nodes),
            edges_(edges)
        {}

        PlanarPrimitive(const PlanarPrimitive& prim):
            type_(prim.type_),
            nodes_(prim.nodes_),
            edges_(prim.edges_)
        {}

        Type getType() const
        {
            return type_;
        }

        const PlanarGraph::NodeCollection& getNodes() const
        {
            return nodes_;
        }

        const PlanarGraph::EdgeCollection& getEdges() const
        {
            return edges_;
        }

        PlanarGraph convertToGraph() const
        {
            return PlanarGraph(nodes_, edges_);
        }

    private:
        Type type_;
        PlanarGraph::NodeCollection nodes_;
        PlanarGraph::EdgeCollection edges_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
