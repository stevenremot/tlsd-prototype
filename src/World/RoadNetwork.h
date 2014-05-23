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

// #ifndef WORLD_ROAD_NETWORK_H
// #define WORLD_ROAD_NETWORK_H

#include "../Graphics/Render/ModelableInterface.h"
#include "../Graph/PlanarGraph.h"

namespace World
{
    /**
     * Class representing a road network
     *
     * A road network is a graph, and some geometrical rules
     */
    class RoadNetwork: public Graphics::Render::ModelableInterface
    {
    public:
        RoadNetwork(const Graph::PlanarGraph& graph,
                    float roadSize,
                    const Graphics::Color& color):
            graph_(graph),
            roadSize_(roadSize),
            color_(color)
        {
            updateModel();
        }

        Graph::PlanarGraph& getGraph()
        {
            return graph_;
        }

        const Graph::PlanarGraph& getGraph() const
        {
            return graph_;
        }

        float getRoadSize() const
        {
            return roadSize_;
        }

        virtual const Graphics::Render::Model3D& getModel() const
        {
            return model_;
        }

    private:
        Graph::PlanarGraph graph_;
        float roadSize_;
        Graphics::Color color_;
        Graphics::Render::Model3D model_;

        void updateModel();
    };
}

// #endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
