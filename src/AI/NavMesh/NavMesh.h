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

#ifndef AI_NAVMESH_NAVMESH_H
#define AI_NAVMESH_NAVMESH_H

#include <map>
#include "VertexIdGenerator.h"
#include "../../Graph/PlanarGraph.h"

namespace AI
{
    namespace NavMesh
    {

        /**
         * Class for Navigation Mesh.
         * Represents a graph made of polygonal nodes.
         */
        class NavMesh
        {
        public:
            typedef std::vector<VertexIdGenerator::VertexId> VerticesIdsList;
            typedef std::map<Graph::PlanarNode, VerticesIdsList> PolygonsMap;
            typedef std::map<Graph::PlanarEdge, float> WeightMap;
            typedef std::map<VertexIdGenerator::VertexId,Geometry::Vec2Df> VerticesMap;
            typedef std::map<Graph::PlanarEdge, std::pair<const Geometry::Vec2Df&, const Geometry::Vec2Df&> > BordersMap;

            NavMesh();

            /**
            * Add a new vertex to the graph and return its new vertexId.
            * If the vertex was already in the graph, return its current vertexId.
            */
            VertexIdGenerator::VertexId addVertex(const Geometry::Vec2Df& vertexPosition);
            /**
             * Add a new node to the graph.
             * TODO : return the current node if its already in the graph.
             */
            Graph::PlanarNode& addNode(const Geometry::Vec2Df& position, const VerticesIdsList& verticesIdsList);
            //Graph::PlanarNode& addNode(const Geometry::Vec2Df& position, const std::vector<Geometry::Vec2Df>& verticesList);
            /**
            * Add a new edge to the graph.
            * Edge's weight is added to the weight map and the common border of the two nodes of the navmesh is added to the borders map.
            */
            Graph::PlanarEdge addEdge(const Graph::PlanarNode& node1, const Graph::PlanarNode& node2, float weight);

            /**
             * Remove the node from the graph.
             * Also remove it from the polygons map and remove its edges from the weight map
             */
            void removeNode(const Graph::PlanarNode& node);

            void removeEdge(const Graph::PlanarEdge& edge);

            /**
             * Get the node containing the position
             */
            bool getNode(const Geometry::Vec2Df& position, Graph::PlanarNode& node) const;

            // Getters
            PolygonsMap& getPolygonsMap() {return polygonsMap_;}
            const PolygonsMap& getPolygonsMap() const{return polygonsMap_;}
            const Geometry::Vec2Df& getVertexById(VertexIdGenerator::VertexId vertexId) const;
            const VerticesMap& getVerticesMap() const {return vertices_;}


            /**
             * Temp (to use svgDRawer in tests)
             */
            const Graph::PlanarGraph& getGraph() const {return graph_;}
        private:

            Graph::PlanarGraph graph_;
            /**
            * List of all the vertices of the polygonal nodes.
            */
            //VerticesList vertices_;
            /**
            * Map of all the vertices of the polygonal nodes.
            */
            VerticesMap vertices_;
            /**
            * Each polygonal node is associated to the list of the vertices ids of its polygon.
            */
            PolygonsMap polygonsMap_;
            /**
            * Weight map for edges
            */
            WeightMap weightMap_;
            /**
            * For each edge, gives the common border of the two polygonal nodes of the edge.
            */
            BordersMap bordersMap_;
        };
    }
}
#endif // AI_NAVMESH_NAVMESH_H
