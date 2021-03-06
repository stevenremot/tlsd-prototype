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

#include "IntersectionConstraint.h"

#include <cmath>

#include "../../../Graph/PlanarGraph.h"
#include "EdgeSplitQueryInserter.h"
#include "RoadUtil.h"

using Graph::PlanarNode;
using Graph::PlanarEdge;
using Graph::PlanarGraph;
using Geometry::Vec2Df;

namespace World
{
    namespace Generation
    {
        namespace City
        {
            void IntersectionConstraint::insert(
                RoadQuery& query,
                const RoadNetwork& network
            ) {
                if (query.getState() != RoadQuery::CancelledState)
                {
                    Vec2Df intersection;
                    PlanarEdge intersectedEdge;
                    const Vec2Df& origin = query.getOriginNode().getPosition();

                    if (getNearestIntersection(
                            query,
                            network.getGraph(),
                            intersection,
                            intersectedEdge
                        ))
                    {
                        float length = (origin - intersection).getLength();
                        if (length < minimalLength_)
                        {
                            query.setState(RoadQuery::CancelledState);
                        }
                        else
                        {
                            query.setState(RoadQuery::DoneState);
                            query.setLength(length);
                            query.setInserter(new EdgeSplitQueryInserter(
                                                   intersectedEdge,
                                                   intersection
                                               ));
                        }
                    }
                }
            }
        }
    }
}
