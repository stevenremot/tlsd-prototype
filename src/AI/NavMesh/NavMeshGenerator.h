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

#ifndef AI_NAVMESH_NAVMESHGENERATOR_H
#define AI_NAVMESH_NAVMESHGENERATOR_H

#include <map>

#include "NavMeshContainer.h"
#include "NavMeshGeneratorEvent.h"
#include "Obstacle.h"
#include "../../Event/EventListenerInterface.h"

#include "../../tests/navmesh.h"
namespace AI
{
    namespace NavMesh
    {

        class NodesArrayMap
        {
        public:
            typedef std::map< std::pair<unsigned int, unsigned int>, Graph::PlanarNode > NodesArray;
            typedef std::map <const NavMesh*, NodesArray> NodesArraysMap;

            NodesArrayMap();
            void insertNewNodesArray(const NavMesh& navMesh);
            void setToNode(const NavMesh& navMesh,
                           const Geometry::Vec2Df& lowerLeftPoint,
                           const Geometry::Vec2Df& upperRightPoint,
                           const Graph::PlanarNode& node);

            void clean(const NavMesh& navMesh,
                           const Geometry::Vec2Df& lowerLeftPoint,
                           const Geometry::Vec2Df& upperRightPoint);

            void cleanAll(const NavMesh& navMesh);

            NodesArraysMap& getMap() {return map_;}
            NodesArray& getNodesArray(const NavMesh& navMesh) {return map_.at(&navMesh);}

        private:
            NodesArraysMap map_;
        };

        /**
         * Generate navmeshes
         * Listen to the events related to the navigation meshes.
         * For each chunk, navigation mesh is generated.
         * All the polygonal nodes are rectangles whose height and width are bigger than the defined minimum size of cell
         *
         */
        class NavMeshGenerator : public Event::EventListenerInterface
        {
        public:

            /**
             * Minimum width and height of a polygonal node
             */
            const static float minSizeOfCell_;

            typedef std::map<Rectangle, NavMesh*> NavMeshesMap;
            typedef std::vector<NavMesh*> NavMeshesList;

            NavMeshGenerator(NavMeshContainer& navMeshContainer);

            virtual void call(const Event::Event& event);

            NavMeshesList getNavMeshes() const {return navMeshesList_;}
            /**
             * Create a new navigation mesh
             */
            NavMesh* createNewNavMesh(const Geometry::Vec2Df& lowerLeftPoint, const Geometry::Vec2Df& upperRightPoint);
            /**
             * Called when a new obstacle is added
             * Look for all the navmeshes intersecting the obstacle and update them
             */
            NavMeshesList updateNavMeshes(const Obstacle& obstacle);
            /**
             * Look for all the nodes of the navmeshes intersecting the obstacle.
             * Divide them until the new nodes don't intersect the obstacle or have reached the minimum size of cell
             */
        public:

            void updateNavMesh(NavMesh& navMesh, const Obstacle& obstacle);

            /**
             * Divide a node in 4 cells (North-West, South-West, South-East and North-East).
             * For each cell, check if it intersects the obtacle.
             * If so, divide it in 4, otherwise build a new polygonal node.
             * Continue until the minimimal size of cell is reached
             *
             * ** Warning **
             * This function add new nodes to the graph but do not add the edges
             * Use reconnectGraph to add the missing edges
             */
            void divideCell(NavMesh& navMesh,const NavMesh::VerticesIdsList& verticesIds, const Obstacle& obstacle);
            void reconnectGraph(NavMesh& navMesh);
            /**
             * Map containing all the navigation meshes.
             * Key : lower-left and upper-right corners of the region partitionned by the navigation mesh.
             */
            NavMeshesMap navMeshesMap_;
            NavMeshesList navMeshesList_;

            /**
             * TO DO : 1 map per navmesh
             */
            NodesArrayMap nodesArrayMap_;
            NavMeshContainer& navMeshes_;

        };
    }
}

#endif // AI_NAVMESH_NAVMESHGENERATOR_H
