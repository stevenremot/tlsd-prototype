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

#ifndef TESTS_SVG_DRAWER_H
#define TESTS_SVG_DRAWER_H

#include <sstream>
#include "../Graph/PlanarGraph.h"

namespace Test
{
    /**
     * A simple class to generate SVG diagrams for testing
     */
    class SvgDrawer
    {
    public:
        SvgDrawer(unsigned int width, unsigned int height):
            width_(width),
            height_(height)
        {
            content_ << "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
                     << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\""
                     << width_ << "\" height=\"" << height_ << "\">"
                     << "<g transform=\"translate("
                     << width_ / 2 << " " << height_ / 2
                     << ")\">" ;
        }

        void end()
        {
            content_ << "</g></svg>";
        }

        const std::stringstream& getContent() const { return content_; };

        void drawLine(int x1, int y1, int x2, int y2, const char* color)
        {
            content_ << "<line x1=\"" << x1 << "\" y1=\"" << y1
                     << "\" x2=\"" << x2 << "\" y2=\"" << y2
                     << "\" stroke=\"" << color << "\" />";
        }

        void drawCircle(int x, int y, int r, const char* color)
        {
            content_ << "<circle cx=\"" << x << "\" cy=\"" << y
                     << "\" r=\"" << r << "\" fill=\"" << color << "\" />";
        }

        void drawGraph(const Graph::PlanarGraph& graph)
        {
            const Graph::PlanarGraph::EdgeCollection& edges = graph.getEdges();
            for (unsigned int i = 0; i < edges.size(); i++)
            {
                const Graph::PlanarEdge& edge = edges[i];
                const Geometry::Vec2Df& p1 = edge.getFirstNode().getPosition();
                const Geometry::Vec2Df& p2 = edge.getSecondNode().getPosition();

                drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY(), "black");
            }

            const Graph::PlanarGraph::NodeCollection& nodes = graph.getNodes();
            for (unsigned int i = 0; i < nodes.size(); i++)
            {
                const Graph::PlanarNode& node = nodes[i];
                const Geometry::Vec2Df& p = node.getPosition();

                drawCircle(p.getX(), p.getY(), 1, "red");
            }
        }
    private:
        unsigned int width_;
        unsigned int height_;
        std::stringstream content_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
