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

        PlanarEdge() {};
        PlanarEdge(const PlanarNode& firstNode,
                   const PlanarNode& secondNode);

        PlanarEdge(const PlanarEdge& edge);
        PlanarEdge& operator=(const PlanarEdge& edge);

        bool operator==(const PlanarEdge& edge) const;
        bool operator!=(const PlanarEdge& edge) const;

        // Getters and setters
        PlanarNode& getFirstNode() { return firstNode_; }
        const PlanarNode& getFirstNode() const { return firstNode_; }
        void setFirstNode(const PlanarNode& node) { firstNode_ = node; }

        PlanarNode& getSecondNode() { return secondNode_; }
        const PlanarNode& getSecondNode() const { return secondNode_; }
        void setSecondNode(const PlanarNode& node) { secondNode_ = node; }

        /**
         * Return the direction vector of the edge
         *
         * It is the difference between the second and the first node
         */
        Geometry::Vec2Df getDirection() const;

        /**
         * Return true if the given node is at one extremity of the edge
         */
        bool hasNode(const PlanarNode& node) const;

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

        bool operator<(const PlanarEdge& edge) const
        {
            const Geometry::Vec2Df& p11 = firstNode_.getPosition();
            const Geometry::Vec2Df& p12 = secondNode_.getPosition();
            const Geometry::Vec2Df& p21 = edge.firstNode_.getPosition();
            const Geometry::Vec2Df& p22 = edge.secondNode_.getPosition();

            return (p11 < p21) || (p11 == p21 && p12 < p22);
        }

    private:
        PlanarNode firstNode_;
        PlanarNode secondNode_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
