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

#include "NeighbourEdgeConstraint.h"

#include "RoadUtil.h"
#include "EdgeSplitQueryInserter.h"

using Geometry::Vec2Df;
using Graph::PlanarEdge;

namespace World
{
    namespace Generation
    {
        namespace City
        {
            void NeighbourEdgeConstraint::insert(
                    RoadQuery& query,
                    const RoadNetwork& network
            ) {
                if (query.getState() == RoadQuery::PendingState)
                {
                    Vec2Df projection;
                    PlanarEdge projectionEdge;
                    const Vec2Df& origin = query.getOriginNode().getPosition();

                    if (getNearestProjection(
                            query,
                            network.getGraph(),
                            projection,
                            projectionEdge
                        ))
                    {
                        Vec2Df offset = projection - origin;
                        if (offset.getLength() <= radius_)
                        {
                            query.setState(RoadQuery::DoneState);

                            query.setLength(offset.getLength());
                            query.setOrientation(offset.getOrientation());
                            query.setInserter(new EdgeSplitQueryInserter(
                                                  projectionEdge,
                                                  projection
                                              ));
                        }
                    }
                }
            }
        }
    }
}
