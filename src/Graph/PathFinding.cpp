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

#include "PathFinding.h"

#include <map>
#include <cfloat>

using std::vector;
using std::map;

namespace Graph
{
    float distance(const PlanarNode& firstNode, const PlanarNode& secondNode)
    {
        return (firstNode.getPosition() - secondNode.getPosition()).getLength();
    }


    bool isNodeInList(const PlanarNode& node, const PlanarGraph::NodeCollection& nodesList)
    {
        bool found = false;
        for (PlanarGraph::NodeCollection::const_iterator it = nodesList.begin(); it != nodesList.end(); ++it)
            if ((*it) == node)
                return true;
        return found;
    }

    bool AStar(const PlanarGraph& graph,
               const PlanarNode& startNode,
               const PlanarNode& goalNode,
               HeuristicFunction h,
               DistanceFunction w,
               PlanarGraph::NodeCollection& path)
    {
        path.clear();

        const PlanarGraph::NodeCollection& nodes = graph.getNodes();

        PlanarGraph::NodeCollection closedSet;
        PlanarGraph::NodeCollection openSet;

        openSet.push_back(startNode);

        map<PlanarNode, PlanarNode> came_from;

        map<PlanarNode, float> g_score;
        map<PlanarNode, float> f_score;

        PlanarGraph::NodeCollection::const_iterator nodesIt;
        // Initialize g_score and f_score
        for(nodesIt = nodes.begin(); nodesIt != nodes.end(); ++nodesIt)
        {
            const PlanarNode& node = (*nodesIt);
            if(node == startNode)
            {
                g_score[node] = 0.0;
                f_score[node] = g_score[node] + h(node, goalNode);
            }
            else
            {
                g_score[node] = FLT_MAX;
                f_score[node] = FLT_MAX;
            }
        }

        while(openSet.size() > 0)
        {
            // Find the lowest f_score
            PlanarGraph::NodeCollection::iterator currentNodePosition = openSet.begin();
            float lowest_f_score = f_score.at(openSet.at(0));
            for (PlanarGraph::NodeCollection::iterator it = openSet.begin(); it != openSet.end(); ++it)
            {
                const PlanarNode& n = (*it);
                if (f_score.at(n) < lowest_f_score)
                {
                    lowest_f_score = f_score.at(n);
                    currentNodePosition = it;
                }
            }

            PlanarNode currentNode = (*currentNodePosition);
            if (currentNode == goalNode)
            {
                // Retrieve the path
                PlanarNode formerNode = goalNode;
                while (!(formerNode == startNode))
                {
                    path.insert(path.begin(), formerNode);
                    formerNode = came_from.at(formerNode);
                }
                path.insert(path.begin(),startNode);
                return true;
            }
            // Remove current node from open set
            openSet.erase(currentNodePosition);
            // Add current node to closed set
            closedSet.push_back(currentNode);
            // Get neighbours
            const PlanarGraph::EdgeCollection& neighboursEdges = graph.getNeighbourEdges(currentNode);
            PlanarGraph::EdgeCollection::const_iterator edgesIt;
            for (edgesIt = neighboursEdges.begin(); edgesIt != neighboursEdges.end(); ++edgesIt)
            {
                const PlanarEdge& edge = (*edgesIt);
                const PlanarNode& neighbourNode = edge.getOtherNode(currentNode);
                // Check if the neighbour is not in the closed set
                if (isNodeInList(neighbourNode, closedSet))
                    continue;
                float tentative_g_score;

                tentative_g_score = g_score.at(currentNode) + w(currentNode, neighbourNode);

                bool isNodeInOpenSet = isNodeInList(neighbourNode, openSet);
                if ( !isNodeInOpenSet || tentative_g_score < g_score.at(neighbourNode))
                {
                    came_from.insert(std::make_pair(neighbourNode, currentNode));
                    g_score[neighbourNode] = tentative_g_score;
                    f_score[neighbourNode] = g_score[neighbourNode] + h(neighbourNode, goalNode);
                    if (!isNodeInOpenSet)
                        openSet.push_back(neighbourNode);
                }
            }
        }
        return false;
    }

    bool BasicAStar(const PlanarGraph& graph,
                    const PlanarNode& startNode,
                    const PlanarNode& goalNode,
                    PlanarGraph::NodeCollection &path)
    {
        return AStar(graph, startNode, goalNode, &distance, &distance, path);
    }
}
