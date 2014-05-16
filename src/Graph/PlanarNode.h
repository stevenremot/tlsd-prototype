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

#ifndef GRAPH_PLANAR_NODE_H
#define GRAPH_PLANAR_NODE_H

#include <lemon/list_graph.h>

#include "../Geometry/Vec2D.h"

namespace Graph
{
    class PlanarGraph;

    /**
     * Represent a graph node with a 2D position.
     */
    class PlanarNode
    {
    public:
        PlanarNode(const lemon::ListGraph::Node& node,
                   const Geometry::Vec2Df& position);

        PlanarNode(const PlanarNode& node);
        PlanarNode& operator=(const PlanarNode& node);

        // Getters and setters
        Geometry::Vec2Df& getPosition() { return position_; }
        const Geometry::Vec2Df& getPosition() const { return position_; }
        void setPosition(const Geometry::Vec2Df& position) { position_ = position;}

        // Operators
        bool operator==(const PlanarNode& node) const;

        // In order to hide lemon node from the outside of the code,
        // but to let the graph implementation get it.
        friend class PlanarGraph;

    private:
        lemon::ListGraph::Node node_;
        Geometry::Vec2Df position_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
