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

#ifndef GRAPH_PLANAR_EDGE_H
#define GRAPH_PLANAR_EDGE_H

#include <exception>

#include <lemon/list_graph.h>

#include "PlanarNode.h"

namespace Graph
{
    /**
     * Represent a link between two nodes in aplanar graph.
     */
    class PlanarEdge
    {
    public:
        class NotExtremityException: public std::exception
        {
            const char* what() const throw()
            {
                return "Provided node is not and extremity of the edge.";
            }
        };

        PlanarEdge(const PlanarNode& firstNode,
                   const PlanarNode& secondNode,
                   const lemon::ListGraph::Edge edge);

        PlanarEdge(const PlanarEdge& edge);
        PlanarEdge& operator=(const PlanarEdge& edge);

        // Getters and setters
        PlanarNode& getFirstNode() { return firstNode_; }
        const PlanarNode& getFirstNode() const { return firstNode_; }
        void setFirstNode(const PlanarNode& node) { firstNode_ = node; }

        PlanarNode& getSecondNode() { return secondNode_; }
        const PlanarNode& getSecondNode() const { return secondNode_; }
        void setSecondNode(const PlanarNode& node) { secondNode_ = node; }

        /**
         * Return the other extremity of the edge
         *
         * If node is an extremity of the edge, return the other.
         *
         * Otherwise, throw an exception.
         */
        PlanarNode& getNode(const PlanarNode& node);

        /**
         * Return the other extremity of the edge
         *
         * If node is an extremity of the edge, return the other.
         *
         * Otherwise, throw an exception.
         */
        const PlanarNode& getOtherNode(const PlanarNode& node) const;

        // In order to hide lemon edge from the outside of the code,
        // but to let the graph implementation get it.
        friend class PlanarGraph;


    private:
        PlanarNode firstNode_;
        PlanarNode secondNode_;
        lemon::ListGraph::Edge edge_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
