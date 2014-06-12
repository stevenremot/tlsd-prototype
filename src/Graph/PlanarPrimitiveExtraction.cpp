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

#include "PlanarPrimitiveExtraction.h"

#include <map>

#include "PlanarUtil.h"

using std::map;
using Geometry::Vec2Df;

namespace Graph
{
    bool edgeIsCycle(const map<PlanarEdge, bool>& isCycle, const PlanarEdge& edge)
    {
        return isCycle.find(edge) != isCycle.end() && isCycle.at(edge);
    }


    PlanarPrimitive extractSingleton(PlanarGraph& graph, const PlanarNode& node)
    {
        graph.removeNode(node);
        PlanarGraph::NodeCollection nodes;
        PlanarGraph::EdgeCollection edges;

        nodes.push_back(node);
        return PlanarPrimitive(PlanarPrimitive::SingletonType, nodes, edges);
    }

    PlanarPrimitive extractFilament(
        PlanarGraph& graph,
        const map<PlanarEdge, bool>& isCycle,
        const PlanarNode& node,
        const PlanarEdge& edge
    ) {
        if (edgeIsCycle(isCycle, edge))
        {
            /*
             * If the edge has been tagged as belonging to a cycle, we
             * have to remove all edges composing a filament that
             * formed a cycle before.
             *
             * This part of code is intended to run after a minimal
             * cycle has been detected, in order to remove it from the
             * graph.
             */

            PlanarNode n = node;
            PlanarGraph::EdgeCollection edges = graph.getNeighbourEdges(n);

            if (edges.size() >= 3)
            {
                graph.removeEdge(edge);
                n = edge.getOtherNode(n);
                edges = graph.getNeighbourEdges(n);
            }

            PlanarEdge e;
            while (edges.size() == 1 && edgeIsCycle(isCycle, edges.front()))
            {
                e = edges.front();
                graph.removeNode(n);
                n = e.getOtherNode(n);
                edges = graph.getNeighbourEdges(n);
            }

            if (edges.empty())
            {
                graph.removeNode(n);
            }

            return PlanarPrimitive(
                PlanarPrimitive::FilamentType,
                PlanarGraph::NodeCollection(),
                PlanarGraph::EdgeCollection()
            );
        }
        else
        {
            /*
             * This part of code is the real filament primitive
             * extraction.
             *
             * It will remove edges and nodes as long as this is
             * considered a part of a filament.
             */
            PlanarGraph::NodeCollection primNodes;
            PlanarGraph::EdgeCollection primEdges;

            PlanarNode n = node;
            PlanarGraph::EdgeCollection edges = graph.getNeighbourEdges(n);

            if (edges.size() >= 3)
            {
                primNodes.push_back(n);
                primEdges.push_back(edge);
                graph.removeEdge(edge);
                n = edge.getOtherNode(n);
            }

            edges = graph.getNeighbourEdges(n);
            PlanarEdge e = edge;

            while (edges.size() == 1 && !edgeIsCycle(isCycle, e))
            {
                primNodes.push_back(n);
                e = edges.front();
                primEdges.push_back(e);
                graph.removeNode(n);
                n = e.getOtherNode(n);
                edges = graph.getNeighbourEdges(n);
            }

            primNodes.push_back(n);

            if (edges.empty())
            {
                graph.removeNode(n);
            }

            return PlanarPrimitive(
                PlanarPrimitive::FilamentType,
                primNodes,
                primEdges
            );
        }
    }

    PlanarPrimitive extractPrimitive(
        PlanarGraph& graph,
        map<PlanarEdge, bool>& isCycle,
        const PlanarNode& node
    ) {

        // We first do a depth-first walk of the graph until we reach
        // a previously visited node or a dead-end
        PlanarGraph::NodeCollection visited;
        PlanarGraph::EdgeCollection visitedEdges;
        visited.push_back(node);

        PlanarNode currentNode = node;
        PlanarGraph::EdgeCollection firstNeighbours = graph.getNeighbourEdges(node);
        PlanarEdge nextEdge;
        getNextEdge(
            node,
            Vec2Df(0, 1),
            firstNeighbours,
            ClockwiseDirection,
            nextEdge
        );

        PlanarEdge firstNextEdge = nextEdge;
        bool hasNeighbours = true;
        while(hasNeighbours &&
              std::find(
                  visited.begin(),
                  visited.end(),
                  nextEdge.getOtherNode(currentNode)
              ) == visited.end())
        {
            PlanarNode otherNode = nextEdge.getOtherNode(currentNode);
            PlanarGraph::EdgeCollection edges = graph.getNeighbourEdges(otherNode);
            edges.erase(std::find(edges.begin(), edges.end(), nextEdge));
            visited.push_back(otherNode);
            visitedEdges.push_back(nextEdge);
            hasNeighbours = getNextEdge(
                otherNode,
                otherNode.getPosition() - currentNode.getPosition(),
                edges,
                CounterClockwiseDirection,
                nextEdge
            );
            currentNode = otherNode;
        }

        if (!hasNeighbours)
        {
            // We got a dead-end, we have to remove a filament
            return extractFilament(
                graph,
                isCycle,
                currentNode,
                graph.getNeighbourEdges(currentNode).front()
            );
        }
        else if(nextEdge.getOtherNode(currentNode) == node)
        {
            // We came back to the first node, there is a minimal cycle.
            // We create the primitive and remove it from the graph.
            PlanarGraph::NodeCollection primNodes = visited;
            PlanarGraph::EdgeCollection primEdges = visitedEdges;
            primEdges.push_back(nextEdge);

            for (unsigned int i = 0; i < primEdges.size(); i++)
            {
                isCycle[primEdges[i]] = true;
            }

            graph.removeEdge(primEdges.front());

            PlanarGraph::EdgeCollection firstNeighbours =
                graph.getNeighbourEdges(node);

            if (firstNeighbours.size() == 1)
            {
                extractFilament(graph, isCycle, node, firstNeighbours.front());
            }

            PlanarGraph::EdgeCollection secondNeighbours =
                graph.getNeighbourEdges(primNodes[1]);

            if (secondNeighbours.size() == 1 &&
                edgeIsCycle(isCycle, secondNeighbours.front()))
            {
                extractFilament(
                    graph,
                    isCycle,
                    primNodes[1],
                    secondNeighbours.front()
                );
            }

            return PlanarPrimitive(
                PlanarPrimitive::CycleType,
                primNodes,
                primEdges
            );
        }
        else
        {
            // There is a cycle, but not based on the first node.
            // It means the first node is part of a filament.
            // We locate the beginning of it, and remove it.
            currentNode = node;

            PlanarGraph::EdgeCollection neighbours =
                graph.getNeighbourEdges(currentNode);
            nextEdge = firstNextEdge;

            while (neighbours.size() == 2)
            {
                if (neighbours[0] != nextEdge)
                {
                    nextEdge = neighbours[0];
                }
                else
                {
                    nextEdge = neighbours[1];
                }

                currentNode = nextEdge.getOtherNode(currentNode);
                neighbours = graph.getNeighbourEdges(currentNode);
            }

            return extractFilament(graph, isCycle, currentNode, nextEdge);
        }
    }

    PlanarPrimitiveCollection extractPrimitives(const PlanarGraph& graph)
    {
        PlanarGraph g(graph);
        map<PlanarEdge, bool> isCycle;

        PlanarPrimitiveCollection primitives;

        while (!g.getNodes().empty())
        {
            const PlanarNode& node = getFirstNode(g);
            PlanarGraph::EdgeCollection edges = g.getNeighbourEdges(node);

            if (edges.empty())
            {
                primitives.push_back(extractSingleton(g, node));
            }
            else if (edges.size() == 1)
            {
                PlanarPrimitive prim = extractFilament(g, isCycle, node, edges[0]);
                if (!prim.getNodes().empty())
                {
                    primitives.push_back(prim);
                }
            }
            else
            {
                primitives.push_back(extractPrimitive(g, isCycle, node));
            }
        }

        return primitives;
    }


    //////////////////////////////////////////////////
    // Filament removal                             //
    //////////////////////////////////////////////////

    bool cycleContainsFilamentStart(
        const PlanarPrimitive& cycle,
        const PlanarNode& node,
        const PlanarEdge& edge
    ) {

        const PlanarGraph::NodeCollection& cylNodes = cycle.getNodes();
        const PlanarGraph::EdgeCollection& cylEdges = cycle.getEdges();

        unsigned int index;
        bool found = false;

        for (unsigned int i = 0; i < cylNodes.size(); i++)
        {
            if (cylNodes[i] == node)
            {
                found = true;
                index = i;
                break;
            }
        }

        if (found)
        {
            const Vec2Df& firstPos = node.getPosition();

            const Vec2Df firstDirection =
                edge.getOtherNode(node).getPosition() - firstPos;
            const PlanarEdge& edge2 = cylEdges[index];
            const PlanarEdge& edge1 =
                cylEdges[(index + cylEdges.size() - 1) % cylEdges.size()];

            const Vec2Df dir1 =
                firstPos - edge1.getOtherNode(node).getPosition();
            const Vec2Df dir2 =
                edge2.getOtherNode(node).getPosition() - firstPos;

            return isBetween(dir1, dir2, firstDirection, CounterClockwiseDirection);
        }

        return false;
    }

    bool cycleContainsFilament(
        const PlanarPrimitive& cycle,
        const PlanarPrimitive& filament
    ) {
        const PlanarGraph::NodeCollection& filNodes = filament.getNodes();
        const PlanarGraph::EdgeCollection& filEdges = filament.getEdges();

        return
            cycleContainsFilamentStart(cycle, filNodes.front(), filEdges.front()) ||
            cycleContainsFilamentStart(cycle, filNodes.back(), filEdges.back());
    }

    PlanarGraph extractFilamentsInCycles(
        const PlanarGraph& graph,
        const PlanarPrimitiveCollection& primitives
    ) {
        PlanarGraph newGraph(graph);

        PlanarPrimitiveCollection filaments;
        PlanarPrimitiveCollection cycles;

        for (unsigned int i = 0; i < primitives.size(); i++)
        {
            const PlanarPrimitive& prim = primitives[i];
            switch (prim.getType())
            {
            case PlanarPrimitive::CycleType:
                cycles.push_back(prim);
                break;
            case PlanarPrimitive::FilamentType:
                filaments.push_back(prim);
                break;
            default:
                break;
            }
        }

        for (unsigned int i = 0; i < filaments.size(); i++)
        {
            const PlanarPrimitive& filament = filaments[i];
            for (unsigned int j = 0; j < cycles.size(); j++)
            {
                if (cycleContainsFilament(cycles[j], filament))
                {
                    const PlanarGraph::EdgeCollection& edges = filament.getEdges();
                    for (unsigned int k = 0; k < edges.size(); k++)
                    {
                        newGraph.removeEdge(edges[k]);
                    }

                    const PlanarGraph::NodeCollection& nodes = filament.getNodes();
                    for (unsigned int k = 0; k < nodes.size(); k++)
                    {
                        const PlanarNode& node = nodes[k];
                        if (newGraph.getNeighbourEdges(node).empty())
                        {
                            newGraph.removeNode(node);
                        }
                    }
                }
            }
        }

        return newGraph;
    }
}
