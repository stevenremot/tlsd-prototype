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

#include "NavMesh.h"

#include <stdexcept>

#include "../../Geometry/Polygon2D.h"

using std::vector;

namespace AI
{
    namespace NavMesh
    {
        NavMesh::NavMesh() : graph_()
        {}

        VertexIdGenerator::VertexId NavMesh::addVertex(const Geometry::Vec2Df& vertexPosition)
        {
            // Check if the vertex is already in the map
            VerticesMap::const_iterator it;
            for (it = vertices_.begin(); it != vertices_.end(); ++it)
            {
                if (it->second == vertexPosition)
                    return it->first;
            }
            // If not, add it to the map
            VertexIdGenerator::VertexId newVertexId = VertexIdGenerator::getNewVertexId();
            vertices_.insert(std::make_pair(newVertexId, vertexPosition));
            return newVertexId;
        }

        Graph::PlanarNode NavMesh::addNode(const Geometry::Vec2Df& position, const VerticesIdsList& verticesIdsList)
        {
            Graph::PlanarNode newNode = graph_.addNode(position);
            polygonsMap_.insert(std::make_pair(newNode, verticesIdsList));
            return newNode;
        }

        Graph::PlanarEdge NavMesh::addEdge(const Graph::PlanarNode &node1, const Graph::PlanarNode &node2, float weight)
        {
            Graph::PlanarEdge newEdge = graph_.addEdge(node1,node2);
            weightMap_.insert(std::make_pair(newEdge, weight));
            // Add the border
            return newEdge;
        }

        void NavMesh::removeNode(const Graph::PlanarNode& node)
        {
            PolygonsMap::iterator it = polygonsMap_.find(node);
            if (it == polygonsMap_.end())
                return;
            graph_.removeNode(node);
            polygonsMap_.erase(it);
        }

        void NavMesh::removeEdge(const Graph::PlanarEdge &edge)
        {
            WeightMap::iterator it = weightMap_.find(edge);
            if (it == weightMap_.end())
                return;
            graph_.removeEdge(edge);
        }
        const Geometry::Vec2Df& NavMesh::getVertexById(VertexIdGenerator::VertexId vertexId) const
        {
            // TODO : Exception handling
            return vertices_.at(vertexId);
        }

        bool NavMesh::getNode(const Geometry::Vec2Df& position, Graph::PlanarNode& node) const
        {
            try
            {
                const Graph::PlanarGraph::NodeCollection& nodes = graph_.getNodes();
                Graph::PlanarGraph::NodeCollection::const_iterator nodesIt;
                for(nodesIt = nodes.begin(); nodesIt != nodes.end(); ++nodesIt)
                {
                    const Graph::PlanarNode& currentNode = (*nodesIt);
                    VerticesIdsList verticesIds = polygonsMap_.at(currentNode);
                    std::vector<Geometry::Vec2Df> vertices;
                    for (VerticesIdsList::const_iterator verticesIt = verticesIds.begin(); verticesIt != verticesIds.end(); ++verticesIt)
                    {
                        const Geometry::Vec2Df& v = vertices_.at(*verticesIt);
                        vertices.push_back(v);
                    }
                    Geometry::Polygon2D polygon(vertices);
                    if(polygon.contains(position))
                    {
                        node = currentNode;
                        return true;
                    }
                }
                return false;
            }
            catch (const std::out_of_range& e)
            {
                return false;
            }
        }

    }
}
