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

#ifndef GRAPH_PLANAR_GRAPH_H
#define GRAPH_PLANAR_GRAPH_H

#include <vector>
#include <lemon/list_graph.h>

#include "PlanarNode.h"
#include "PlanarEdge.h"

namespace Graph
{
    class PlanarGraph
    {
    public:
        typedef std::vector<PlanarNode> NodeCollection;
        typedef std::vector<PlanarEdge> EdgeCollection;

        PlanarGraph();
        PlanarGraph(const NodeCollection& nodes, const EdgeCollection& edges);
        PlanarGraph(const PlanarGraph& graph);

        PlanarGraph& operator=(const PlanarGraph& graph);

        // Nodes and edges adding / removal

        /**
         * Insert a node with given position in the graph
         *
         * @return the newly created node
         */
        PlanarNode addNode(const Geometry::Vec2Df& position);

        /**
         * Remove the given node from the graph
         */
        void removeNode(const PlanarNode& node);

        /**
         * Add an edge linking two nodes
         *
         * *TODO* :
         *
         * It would be nice to return a reference in this method, but
         * this reference would currently be modified when
         * /getNeighbourEdges/ is called. It makes no sense, as this
         * method should only read things, but you can see it by
         * returning reference with addEdge and launching tests.
         *
         * @return the newly created edge
         */
        PlanarEdge addEdge(const PlanarNode& firstNode,
                           const PlanarNode& secondNode);

        /**
         * Remove the given edge from the graph
         */
        void removeEdge(const PlanarEdge& edge);

        // Getters and setters

        const NodeCollection& getNodes() const
        {
            return nodeCache_;
        }

        const EdgeCollection& getEdges() const
        {
            return edgeCache_;
        }

        // Graph traversing

        /**
         * Return the edges which node is an extremity of.
         */
        EdgeCollection getNeighbourEdges(const PlanarNode& node);

        /**
         * Return the edges which node is an extremity of.
         */
        EdgeCollection getNeighbourEdges(const PlanarNode& node) const;

    private:
        lemon::ListGraph graph_;
        lemon::ListGraph::NodeMap<PlanarNode> nodes_;
        lemon::ListGraph::EdgeMap<PlanarEdge> edges_;
        NodeCollection nodeCache_;
        EdgeCollection edgeCache_;

        void insertData(const NodeCollection& nodes,
                        const EdgeCollection& edges);
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
