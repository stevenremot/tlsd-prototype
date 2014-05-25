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

#include "QueryCreator.h"

#include <cmath>

using Geometry::Vec2Df;

namespace World
{
    namespace Generation
    {
        namespace City
        {
            QueryCreator::QueryCollection QueryCreator::createQueries(
                const BranchRequest& request
            ) {
                const Graph::PlanarNode& node = request.getInitialNode();
                const Graph::PlanarEdge& edge = request.getInitialEdge();

                Vec2Df direction =
                    node.getPosition() - edge.getOtherNode(node).getPosition();

                float baseOrientation = direction.getOrientation() - M_PI / 2.0;

                QueryCollection queries;

                for (unsigned int i = 0; i < 3; i++)
                {
                    float orientation = baseOrientation +
                        M_PI * static_cast<float>(i) / 2.0 +
                        numberGenerator_.getUniform(-0.25, 0.25);

                    float length = averageLength_ +
                        numberGenerator_.getUniform(
                            -averageLength_ / 2.0,
                            averageLength_ / 2.0
                        );

                    queries.push_back(RoadQuery(
                                          node,
                                          orientation,
                                          length
                                      ));
                }

                return queries;
            }
        }
    }
}
