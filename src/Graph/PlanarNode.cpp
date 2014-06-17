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

#include "PlanarNode.h"

using Geometry::Vec2Df;

namespace Graph
{
    PlanarNode::PlanarNode()
    {}

    PlanarNode::PlanarNode(const Vec2Df& position):
        position_(position)
    {}

    PlanarNode::PlanarNode(const lemon::ListGraph::Node& node,
                           const Geometry::Vec2Df& position):
        node_(node),
        position_(position)
    {}

    PlanarNode::PlanarNode(const PlanarNode& node):
        node_(node.node_),
        position_(node.position_)
    {}

    PlanarNode& PlanarNode::operator=(const PlanarNode& node)
    {
        node_ = node.node_;
        position_ = node.position_;
        return *this;
    }

    bool PlanarNode::operator==(const PlanarNode& node) const
    {
        return position_ == node.position_;
    }

    bool PlanarNode::operator!=(const PlanarNode& node) const
    {
        return position_ != node.position_;
    }

    bool PlanarNode::operator<(const PlanarNode& node) const
    {
        return (position_ < node.position_);
    }

}
