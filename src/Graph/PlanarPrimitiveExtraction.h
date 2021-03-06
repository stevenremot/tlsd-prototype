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

#ifndef PLANAR_PRIMITIVE_EXTRACTION_H
#define PLANAR_PRIMITIVE_EXTRACTION_H

#include <vector>

#include "PlanarPrimitive.h"
#include "PlanarGraph.h"

namespace Graph
{
    typedef std::vector<PlanarPrimitive> PlanarPrimitiveCollection;

    /**
     * Analyze a graph and extract its primitives.
     *
     * Primitives can be :
     * - A singleton : a single node linked to nothing
     * - A filament : a sequence of nodes with only 2 neighbours, belonging
     *                to no cycle
     * - A cycle : A sequence of nodes that come back to its start.
     *             cycles' elements are guaranteed to be given in
     *             counter-clockwise order, and with edge n associated to
     *             node n and node n + 1
     */
    PlanarPrimitiveCollection extractPrimitives(const PlanarGraph& graph);

    /**
     * Return a copy of the given graph, without the filaments contained in cycles.
     *
     * @param graph
     * @param primitives the primitives of the graph, given by extractPrimitives
     */
    PlanarGraph extractFilamentsInCycles(
        const PlanarGraph& graph,
        const PlanarPrimitiveCollection& primitives
    );
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
