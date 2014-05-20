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

#include "PlanarEdge.h"

namespace Graph
{
    PlanarEdge::PlanarEdge(const PlanarNode& firstNode,
                           const PlanarNode& secondNode,
                           const lemon::ListGraph::Edge edge):
        firstNode_(firstNode),
        secondNode_(secondNode),
        edge_(edge)
    {}

    PlanarEdge::PlanarEdge(const PlanarEdge& edge):
        firstNode_(edge.firstNode_),
        secondNode_(edge.secondNode_),
        edge_(edge.edge_)
    {}

    PlanarEdge& PlanarEdge::operator=(const PlanarEdge& edge)
    {
        firstNode_ = edge.firstNode_;
        secondNode_ = edge.secondNode_;
        edge_ = edge.edge_;
        return *this;
    }

    bool PlanarEdge::operator==(const PlanarEdge& edge) const
    {
        return firstNode_ == edge.firstNode_ &&
            secondNode_ == edge.secondNode_;
    }

    bool PlanarEdge::hasNode(const PlanarNode& node)
    {
        return firstNode_ == node || secondNode_ == node;
    }

    PlanarNode& PlanarEdge::getNode(const PlanarNode& node)
    {
        if (node == firstNode_)
        {
            return secondNode_;
        }
        else if (node == secondNode_)
        {
            return firstNode_;
        }
        else
        {
            throw NotExtremityException();
        }
    }

    const PlanarNode& PlanarEdge::getOtherNode(const PlanarNode& node) const
    {
        if (node == firstNode_)
        {
            return secondNode_;
        }
        else if (node == secondNode_)
        {
            return firstNode_;
        }
        else
        {
            throw NotExtremityException();
        }
    }
}
