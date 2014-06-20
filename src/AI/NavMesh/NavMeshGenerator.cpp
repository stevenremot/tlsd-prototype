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

#include "NavMeshGenerator.h"


namespace AI
{
    namespace NavMesh
    {

        NodesArrayMap::NodesArrayMap()
        {
        }

        void NodesArrayMap::insertNewNodesArray(const NavMesh &navMesh)
        {
            if(map_.find(&navMesh) !=  map_.end())
                return;
            NodesArray nodesArray;
            map_.insert(make_pair(&navMesh,nodesArray));

            // Fill the array
            const Graph::PlanarGraph::NodeCollection& nodes = navMesh.getGraph().getNodes();
            const NavMesh::VerticesMap& verticesMap = navMesh.getVerticesMap();
            const NavMesh::PolygonsMap& polygonsMap = navMesh.getPolygonsMap();
            for(Graph::PlanarGraph::NodeCollection::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
            {
                const Graph::PlanarNode& node = *it;
                const NavMesh::VerticesIdsList& verticesIds = polygonsMap.at(node);
                const Geometry::Vec2Df& lowerLeftVertex = verticesMap.at(verticesIds.at(1));
                const Geometry::Vec2Df& upperRightVertex = verticesMap.at(verticesIds.at(3));
                setToNode(navMesh, lowerLeftVertex, upperRightVertex, node);
            }
        }

        void NodesArrayMap::setToNode(const NavMesh& navMesh,
                                      const Geometry::Vec2Df& lowerLeftPoint,
                                      const Geometry::Vec2Df& upperRightPoint,
                                      const Graph::PlanarNode& node)
        {
            int minSizeOfCell = NavMeshGenerator::minSizeOfCell_;
            if(map_.find(&navMesh) == map_.end())
                return;
            NodesArray& nodesArray = map_.at(&navMesh);
            unsigned int min_i = lowerLeftPoint.getX()/minSizeOfCell;
            unsigned int max_i = upperRightPoint.getX()/minSizeOfCell;
            unsigned int min_j = lowerLeftPoint.getY()/minSizeOfCell;
            unsigned int max_j = upperRightPoint.getY()/minSizeOfCell;
            for(unsigned int i = min_i; i < max_i; i++)
            {
                for(unsigned int j = min_j; j < max_j; j++)
                {
                    nodesArray.insert(std::make_pair(std::make_pair(i,j), node));
                }
            }
        }

        void NodesArrayMap::clean(const NavMesh &navMesh,
                       const Geometry::Vec2Df& lowerLeftPoint,
                       const Geometry::Vec2Df& upperRightPoint)
        {
            int minSizeOfCell = NavMeshGenerator::minSizeOfCell_;
            if(map_.find(&navMesh) == map_.end())
                return;
            NodesArray& nodesArray = map_.at(&navMesh);
            int min_i = lowerLeftPoint.getX()/minSizeOfCell;
            int max_i = upperRightPoint.getX()/minSizeOfCell;
            int min_j = lowerLeftPoint.getY()/minSizeOfCell;
            int max_j = upperRightPoint.getY()/minSizeOfCell;
            for(int i = min_i; i < max_i; i++)
            {
                for(int j = min_j; j < max_j; j++)
                {
                    nodesArray.erase(std::make_pair(i,j));
                }
            }
        }

        void NodesArrayMap::cleanAll(const NavMesh &navMesh)
        {
            if(map_.find(&navMesh) == map_.end())
                return;
            NodesArray& nodesArray = map_.at(&navMesh);
            nodesArray.clear();
        }

        const float NavMeshGenerator::minSizeOfCell_ = 16;

        NavMeshGenerator::NavMeshGenerator(NavMeshContainer& navMeshes) : navMeshes_(navMeshes)
        {
        }

        void NavMeshGenerator::createNewNavMesh(const Geometry::Vec2Df& lowerLeftPoint, const Geometry::Vec2Df& upperRightPoint)
        {
            NavMesh* navMesh = new NavMesh();
            NavMesh::VerticesIdsList verticesIdsList;
            // Add 4 vertices corresponding to the corner of the region
            // TO DO : if the new nav mesh has neighbour nav meshes, retrieve the vertices ids of the corners
            // Order : NW -> SW -> SE -> NE
            verticesIdsList.push_back(navMesh->addVertex(Geometry::Vec2Df(lowerLeftPoint.getX(), upperRightPoint.getY())));
            verticesIdsList.push_back(navMesh->addVertex(lowerLeftPoint));
            verticesIdsList.push_back(navMesh->addVertex(Geometry::Vec2Df(upperRightPoint.getX(), lowerLeftPoint.getY())));
            verticesIdsList.push_back(navMesh->addVertex(upperRightPoint));
            // Add the node to the graph
            navMesh->addNode((lowerLeftPoint+upperRightPoint)*0.5, verticesIdsList);


            navMeshes_.setNavMesh(lowerLeftPoint, upperRightPoint, navMesh);
            nodesArrayMap_.insertNewNodesArray(*navMesh);

        }

        void NavMeshGenerator::updateNavMeshes(const Obstacle& obstacle)
        {
            // Find all the navigation meshes intersected by the obstacle.
            NavMeshesList intersectedNavMeshes;
            // We assume that the cell of the navigation mesh and the obstacle's bounding box are squares.
            const Rectangle& rectBB = obstacle.getBoundingBox();

            const NavMeshContainer::NavMeshesMap& navMeshesMap = navMeshes_.getNavMeshesMap();
            NavMeshContainer::NavMeshesMap::const_iterator it;
            for (it = navMeshesMap.begin(); it != navMeshesMap.end(); ++it)
            {
                std::pair<Geometry::Vec2Df, Geometry::Vec2Df> key = it->first;
                Rectangle rectNavMesh(key.first, key.second);

                // intersection rectangle-rectangle
                if(rectNavMesh.intersect(rectBB))
                    intersectedNavMeshes.push_back(it->second);
            }
            for (unsigned int i = 0; i < intersectedNavMeshes.size(); i++)
                updateNavMesh(*(intersectedNavMeshes.at(i)), obstacle);
        }

        void NavMeshGenerator::clean(const Geometry::Vec2Df &lowerLeftPoint, const Geometry::Vec2Df &upperRightPoint)
        {
            NavMesh* navMesh = NULL;
            if(navMeshes_.getNavMesh(lowerLeftPoint, upperRightPoint, navMesh))
            {
                nodesArrayMap_.cleanAll(*navMesh);
            }
        }

        void NavMeshGenerator::updateNavMesh(NavMesh& navMesh, const Obstacle& obstacle)
        {
            NavMesh::PolygonsMap& polygonsMap = navMesh.getPolygonsMap();
            const NavMesh::VerticesMap& vertices = navMesh.getVerticesMap();

            NavMesh::PolygonsMap::const_iterator it;
            Graph::PlanarGraph::NodeCollection nodesToRemove;
            for(it = polygonsMap.begin(); it != polygonsMap.end(); ++it)
            {
                // get the lower-left and upper-right points of the polygonal node
                const NavMesh::VerticesIdsList& verticesIds = it->second;
                const Geometry::Vec2Df& lowerLeftpoint = vertices.at(verticesIds.at(1));
                const Geometry::Vec2Df& upperRightPoint = vertices.at(verticesIds.at(3));
                Rectangle rectNode(lowerLeftpoint, upperRightPoint);
                if(rectNode.intersect(obstacle.getBoundingBox()))
                {
                    nodesArrayMap_.clean(navMesh,lowerLeftpoint, upperRightPoint);

                    // Divide it in 4 nodes
                    divideCell(navMesh, verticesIds, obstacle);

                    // remove the node from the graph
                    nodesToRemove.push_back(it->first);
                    //navMesh.removeNode(it->first);
                }
            }
            while(!nodesToRemove.empty())
            {
                navMesh.removeNode(nodesToRemove.back());
                // remove the node from the graph
                nodesToRemove.pop_back();
            }
            reconnectGraph(navMesh);


        }

        void NavMeshGenerator::divideCell(NavMesh& navMesh,const NavMesh::VerticesIdsList& verticesIds, const Obstacle& obstacle)
        {
            // Assume that the vertices were inserted in the following order : NW -> SW -> SE -> NE
            Geometry::Vec2Df NWPt = Geometry::Vec2Df(navMesh.getVertexById(verticesIds[0]));
            Geometry::Vec2Df SWPt = Geometry::Vec2Df(navMesh.getVertexById(verticesIds[1]));
            Geometry::Vec2Df SEPt = Geometry::Vec2Df(navMesh.getVertexById(verticesIds[2]));
            Geometry::Vec2Df NEPt = Geometry::Vec2Df(navMesh.getVertexById(verticesIds[3]));
            Geometry::Vec2Df CentralPt = Geometry::Vec2Df((NWPt+SEPt)*0.5f);

            // Check the size of the cell
            if(std::abs((NEPt-NWPt).getX())<= minSizeOfCell_ || std::abs((NWPt - SWPt).getY()) <= minSizeOfCell_)
                return;

            VertexIdGenerator::VertexId centralVertexId = navMesh.addVertex(CentralPt);
            VertexIdGenerator::VertexId northVertexId = navMesh.addVertex((NWPt+NEPt)*0.5f);
            VertexIdGenerator::VertexId westVertexId = navMesh.addVertex((NWPt+SWPt)*0.5f);
            VertexIdGenerator::VertexId eastVertexId = navMesh.addVertex((NEPt+SEPt)*0.5f);
            VertexIdGenerator::VertexId southVertexId = navMesh.addVertex((SWPt+SEPt)*0.5f);

            const Rectangle& obstacleBB = obstacle.getBoundingBox();
            // North-West node
            Rectangle NWCell(navMesh.getVertexById(westVertexId), navMesh.getVertexById(northVertexId));
            NavMesh::VerticesIdsList NWVerticesIds;
            NWVerticesIds.push_back(verticesIds[0]);
            NWVerticesIds.push_back(westVertexId);
            NWVerticesIds.push_back(centralVertexId);
            NWVerticesIds.push_back(northVertexId);

            if(NWCell.intersect(obstacleBB))
            {
                divideCell(navMesh, NWVerticesIds, obstacle);
            }
            else
            {
                const Graph::PlanarNode& node = navMesh.addNode((NWPt+CentralPt)*0.5f, NWVerticesIds);
                nodesArrayMap_.setToNode(navMesh,NWCell.getLowerLeftPoint(), NWCell.getUpperRightPoint(), node);

            }
            // South-West node
            Rectangle SWCell(SWPt, CentralPt);
            NavMesh::VerticesIdsList SWVerticesIds;
            SWVerticesIds.push_back(westVertexId);
            SWVerticesIds.push_back(verticesIds[1]);
            SWVerticesIds.push_back(southVertexId);
            SWVerticesIds.push_back(centralVertexId);

            if(SWCell.intersect(obstacleBB))
            {
                divideCell(navMesh, SWVerticesIds, obstacle);
            }
            else
            {
                const Graph::PlanarNode& node = navMesh.addNode((SWPt+CentralPt)*0.5f, SWVerticesIds);
                nodesArrayMap_.setToNode(navMesh,SWCell.getLowerLeftPoint(), SWCell.getUpperRightPoint(), node);
            }
            // South-East node
            Rectangle SECell(navMesh.getVertexById(southVertexId), navMesh.getVertexById(eastVertexId));
            NavMesh::VerticesIdsList SEVerticesIds;
            SEVerticesIds.push_back(centralVertexId);
            SEVerticesIds.push_back(southVertexId);
            SEVerticesIds.push_back(verticesIds[2]);
            SEVerticesIds.push_back(eastVertexId);

            if(SECell.intersect(obstacleBB))
            {
                divideCell(navMesh, SEVerticesIds, obstacle);
            }
            else
            {
                const Graph::PlanarNode& node = navMesh.addNode((SEPt+CentralPt)*0.5f, SEVerticesIds);
                nodesArrayMap_.setToNode(navMesh,SECell.getLowerLeftPoint(), SECell.getUpperRightPoint(), node);
            }
            // North-East node
            Rectangle NECell(CentralPt, NEPt);
            NavMesh::VerticesIdsList NEVerticesIds;
            NEVerticesIds.push_back(northVertexId);
            NEVerticesIds.push_back(centralVertexId);
            NEVerticesIds.push_back(eastVertexId);
            NEVerticesIds.push_back(verticesIds[3]);

            if(NECell.intersect(obstacleBB))
            {
                divideCell(navMesh, NEVerticesIds, obstacle);
            }
            else
            {
                const Graph::PlanarNode& node = navMesh.addNode((NEPt+CentralPt)*0.5f, NEVerticesIds);
                nodesArrayMap_.setToNode(navMesh,NECell.getLowerLeftPoint(), NECell.getUpperRightPoint(), node);
            }
        }

        void NavMeshGenerator::reconnectGraph(NavMesh& navMesh)
        {
           const NodesArrayMap::NodesArray& nodesArray = nodesArrayMap_.getNodesArray(navMesh);

           unsigned int max_i = 0;
           unsigned int max_j = 0;
           for (NodesArrayMap::NodesArray::const_iterator it  = nodesArray.begin(); it != nodesArray.end(); ++it)
           {
               std::pair<unsigned int, unsigned int> key = it->first;
               if(key.first > max_i) max_i = key.first;
               if(key.second > max_j) max_j = key.second;
           }

           for (unsigned int i = 0; i < max_i + 1; i++)
           {
               for (unsigned int j = 0; j < max_j + 1; j++)
               {
                   if(nodesArray.find(std::make_pair(i,j)) != nodesArray.end())
                   {
                       const Graph::PlanarNode& node = nodesArray.at(std::make_pair(i,j));
                       if (i > 0)
                       {
                           if(nodesArray.find(std::make_pair(i-1,j)) != nodesArray.end())
                           {
                               const Graph::PlanarNode& leftNode = nodesArray.at(std::make_pair(i-1,j));
                               if(!(leftNode == node))
                                   navMesh.addEdge(leftNode, node,(leftNode.getPosition()-node.getPosition()).getLength());
                           }
                       }
                       if (j > 0)
                       {
                           if(nodesArray.find(std::make_pair(i,j-1)) != nodesArray.end())
                           {
                               const Graph::PlanarNode& upperNode = nodesArray.at(std::make_pair(i,j-1));
                               if(!(upperNode == node))
                                   navMesh.addEdge(upperNode, node,(upperNode.getPosition()-node.getPosition()).getLength());
                           }
                       }
                   }
               }
           }
        }
    }

}
