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

using Geometry::Vec2Df;

namespace Graph
{
    PlanarGraph::PlanarGraph():
        graph_(),
        nodes_(graph_),
        edges_(graph_)
    {
    }

    PlanarGraph::PlanarGraph(const NodeCollection& nodes,
                             const EdgeCollection& edges):
        graph_(),
        nodes_(graph_),
        edges_(graph_)
    {
        for (unsigned int i = 0; i < nodes.size(); i++)
        {
            const PlanarNode& node = nodes[i];
            addNode(node.getPosition());
        }

        for (unsigned int i = 0; i < edges.size(); i++)
        {
            const PlanarEdge& edge = edges[i];
            addEdge(edge.getFirstNode(), edge.getSecondNode());
        }
    }

    PlanarNode& PlanarGraph::addNode(const Vec2Df& position)
    {
        for (unsigned int i = 0; i < nodeCache_.size(); i++)
        {
            PlanarNode& currentNode = nodeCache_[i];
            if (currentNode.getPosition() == position)
            {
                return currentNode;
            }
        }

        lemon::ListGraph::Node lemonNode = graph_.addNode();
        nodeCache_.push_back(PlanarNode(lemonNode, position));
        PlanarNode& newNode = nodeCache_[nodeCache_.size() - 1];
        nodes_[lemonNode] = newNode;

        return newNode;
    }

    void PlanarGraph::removeNode(const PlanarNode& node)
    {
        EdgeCollection neighbours = getNeighbourEdges(node);
        for (unsigned int i = 0; i < neighbours.size(); i++)
        {
            removeEdge(neighbours[i]);
        }

        graph_.erase(node.node_);
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

        lemon::ListGraph::Edge lemonEdge = graph_.addEdge(
            firstNode.node_,
            secondNode.node_
        );
        edgeCache_.push_back(PlanarEdge(firstNode, secondNode, lemonEdge));
        PlanarEdge& newEdge = edgeCache_[edgeCache_.size() - 1];
        edges_[lemonEdge] = newEdge;

        return newEdge;
    }

    void PlanarGraph::removeEdge(const PlanarEdge& edge)
    {
        graph_.erase(edge.edge_);
        edgeCache_.erase(std::find(edgeCache_.begin(), edgeCache_.end(), edge));
    }

    PlanarGraph::EdgeCollection PlanarGraph::getNeighbourEdges(const PlanarNode& node)
    {
        EdgeCollection edges;
        lemon::ListGraph::IncEdgeIt edge(graph_, node.node_);
        for (; edge != lemon::INVALID; ++edge)
        {
            PlanarEdge& planarEdge = edges_[edge];
            edges.push_back(planarEdge);
        }

        return edges;
    }

    PlanarGraph::EdgeCollection PlanarGraph::getNeighbourEdges(const PlanarNode& node) const
    {
        EdgeCollection edges;
        lemon::ListGraph::IncEdgeIt edge(graph_, node.node_);
        for (; edge != lemon::INVALID; ++edge)
        {
            const PlanarEdge& planarEdge = edges_[edge];
            edges.push_back(planarEdge);
        }

        return edges;
    }

}
