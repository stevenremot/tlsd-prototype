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

#include "PlanarGraph.h"

#include <map>
#include <algorithm>

using Geometry::Vec2Df;

namespace Graph
{
    PlanarGraph::PlanarGraph():
        nodeCache_(),
        edgeCache_()
    {}

    PlanarGraph::PlanarGraph(const NodeCollection& nodes,
                             const EdgeCollection& edges):
        nodeCache_(nodes),
        edgeCache_(edges)
    {}

    PlanarGraph::PlanarGraph(const PlanarGraph& graph):
        nodeCache_(graph.nodeCache_),
        edgeCache_(graph.edgeCache_)
    {}

    PlanarGraph& PlanarGraph::operator=(const PlanarGraph& graph)
    {
        nodeCache_ = graph.nodeCache_;
        edgeCache_ = graph.edgeCache_;

        return *this;
    }

    PlanarNode PlanarGraph::addNode(const Vec2Df& position)
    {
        for (unsigned int i = 0; i < nodeCache_.size(); i++)
        {
            PlanarNode& currentNode = nodeCache_[i];
            if (currentNode.getPosition() == position)
            {
                return currentNode;
            }
        }

        nodeCache_.push_back(PlanarNode(position));
        return nodeCache_[nodeCache_.size() - 1];
    }

    void PlanarGraph::removeNode(const PlanarNode& node)
    {
        EdgeCollection neighbours = getNeighbourEdges(node);
        for (unsigned int i = 0; i < neighbours.size(); i++)
        {
            removeEdge(neighbours[i]);
        }

        nodeCache_.erase(std::find(nodeCache_.begin(), nodeCache_.end(), node));
    }

    PlanarEdge PlanarGraph::addEdge(const PlanarNode& firstNode,
                                    const PlanarNode& secondNode)
    {
        for (unsigned int i = 0; i < edgeCache_.size(); i++)
        {
            PlanarEdge& edge = edgeCache_[i];
            if (edge.hasNode(firstNode) && edge.hasNode(secondNode))
            {
                return edge;
            }
        }

        addNode(firstNode.getPosition());
        addNode(secondNode.getPosition());

        edgeCache_.push_back(PlanarEdge(firstNode, secondNode));
        return edgeCache_[edgeCache_.size() - 1];
    }

    void PlanarGraph::removeEdge(const PlanarEdge& edge)
    {
        edgeCache_.erase(std::find(edgeCache_.begin(), edgeCache_.end(), edge));
    }

    PlanarGraph::EdgeCollection PlanarGraph::getNeighbourEdges(const PlanarNode& node)
    {
        EdgeCollection edges;
        for (auto edge : edgeCache_)
        {
            if (edge.hasNode(node))
            {
                edges.push_back(edge);
            }
        }

        return edges;
    }

    PlanarGraph::EdgeCollection PlanarGraph::getNeighbourEdges(const PlanarNode& node) const
    {
        EdgeCollection edges;
        for (auto edge : edgeCache_)
        {
            if (edge.hasNode(node))
            {
                edges.push_back(edge);
            }
        }

        return edges;
    }
}
