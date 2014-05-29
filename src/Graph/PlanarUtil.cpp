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

#include "PlanarUtil.h"

using Geometry::Vec2Df;

namespace Graph
{
    bool isBetween(const Vec2Df& baseDirection,
                   const Vec2Df& nextDirection,
                   const Vec2Df& consideredDirection,
                   Direction clockwise)
    {
        const bool isConvex = nextDirection.dot(baseDirection.getOrthogonal()) >= 0;
        const Vec2Df consideredOrthogonal = consideredDirection.getOrthogonal();

        const float nextDotCons = nextDirection.dot(consideredOrthogonal);
        const float baseDotCons = baseDirection.dot(consideredOrthogonal);

        if (clockwise == ClockwiseDirection)
        {
            if ((isConvex && (nextDotCons >= 0 || baseDotCons >= 0)) ||
                (!isConvex && (nextDotCons) >= 0 && baseDotCons >= 0))
            {
                return true;
            }
            return false;
        }
        else
        {
            if ((isConvex && nextDotCons <= 0 && baseDotCons <= 0) ||
                (!isConvex && (nextDotCons <= 0 || baseDotCons <= 0)))
            {
                return true;
            }
            return false;
        }

        return false;
    }

    bool getNextEdge(const PlanarNode& commonNode,
                     const Geometry::Vec2Df& baseDirection,
                     const PlanarGraph::EdgeCollection& edges,
                     Direction clockwise,
                     PlanarEdge& edge)
    {
        if (edges.empty())
        {
            return false;
        }

        const Vec2Df& p1 = commonNode.getPosition();

        edge = edges[0];
        Vec2Df nextDirection = edge.getOtherNode(commonNode).getPosition() - p1;

        for (unsigned int i = 0; i < edges.size(); i++)
        {
            const PlanarEdge& currentEdge = edges[i];
            Vec2Df currentDirection =
                currentEdge.getOtherNode(commonNode).getPosition() - p1;

            if (isBetween(baseDirection, nextDirection, currentDirection, clockwise))
            {
                edge = currentEdge;
                nextDirection = currentDirection;
            }
        }

        return true;
    }

    const PlanarNode& getFirstNode(const PlanarGraph& graph)
    {

        const PlanarGraph::NodeCollection& nodes = graph.getNodes();

        PlanarNode node = nodes[0];
        Vec2Df position = node.getPosition();
        int index = 0;

        for (unsigned int i = 1; i < nodes.size(); i++)
        {
            const PlanarNode& currentNode = nodes[i];
            const Vec2Df& currentPosition = currentNode.getPosition();
            if (currentPosition.getX() < position.getX() ||
                (currentPosition.getX() == position.getX() &&
                 currentPosition.getY() < position.getY()))
            {
                node = currentNode;
                position = currentPosition;
                index =  i;
            }
        }

        return nodes[index];
    }
}
