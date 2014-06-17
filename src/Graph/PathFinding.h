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

#ifndef GRAPH_PATHFINDING_H
#define GRAPH_PATHFINDING_H

#include <vector>

#include "PlanarGraph.h"

namespace Graph
{
    typedef float(*HeuristicFunction) (const PlanarNode& currentNode, const PlanarNode& goalNode);
    typedef float(*DistanceFunction) (const PlanarNode& firstNode, const PlanarNode& secondNode);

    bool isNodeInList(const PlanarNode& node, const PlanarGraph::NodeCollection& nodesList);

    /**
     * A* algorithm
     * Look for a path from the start node to the goal node
     * @param h : heuristic function. Used for determine how "far" is the currenty node to the targetNode
     * @return true if a path exists
     */
    bool AStar(const PlanarGraph& graph,
               const PlanarNode& startNode,
               const PlanarNode& goalNode,
               HeuristicFunction h,
               DistanceFunction w,
               PlanarGraph::NodeCollection &path);

    float distance(const PlanarNode& firstNode, const PlanarNode& secondNode);

    /**
     * Heuristic function : distance between the positions of the current and goal nodes
     * Weight Function : distance between the position of two neighbours nodes
     */
    bool BasicAStar(const PlanarGraph& graph,
                    const PlanarNode& startNode,
                    const PlanarNode& goalNode,
                    PlanarGraph::NodeCollection &path);
}
#endif // GRAPH_PATHFINDING_H
