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

#ifndef WORLD_GENERATION_CITY_ROAD_QUERY_H
#define WORLD_GENERATION_CITY_ROAD_QUERY_H

#include <memory>

#include "../../../Graph/PlanarNode.h"
#include "QueryInserterInterface.h"
#include "QueryInserter.h"

namespace World
{
    namespace Generation
    {
        namespace City
        {
            /**
             * Represent a query to insert a road in the road network
             */
            class RoadQuery
            {
            public:
                enum State { PendingState, CancelledState, DoneState };

                RoadQuery(
                    const Graph::PlanarNode& originNode,
                    float orientation,
                    float length
                ):
                    state_(PendingState),
                    originNode_(originNode),
                    orientation_(orientation),
                    length_(length),
                    inserter_(new QueryInserter())
                {}

                RoadQuery(const RoadQuery& query):
                    state_(query.state_),
                    originNode_(query.originNode_),
                    orientation_(query.orientation_),
                    length_(query.length_),
                    inserter_(query.inserter_)
                {}

                const State& getState() const
                {
                    return state_;
                }

                void setState(const State& state)
                {
                    state_ = state;
                }

                const Graph::PlanarNode& getOriginNode() const
                {
                    return originNode_;
                }

                float getOrientation() const
                {
                    return orientation_;
                }

                void setOrientation(float orientation)
                {
                    orientation_ = orientation;
                }

                float getLength() const
                {
                    return length_;
                }

                void setLength(float length)
                {
                    length_ = length;
                }

                QueryInserterInterface& getInserter()
                {
                    return *inserter_;
                }

                void setInserter(QueryInserterInterface* inserter)
                {
                    inserter_ = std::shared_ptr<QueryInserterInterface>(inserter);
                }

            private:
                State state_;
                Graph::PlanarNode originNode_;
                float orientation_;
                float length_;
                std::shared_ptr<QueryInserterInterface> inserter_;
            };
        }
    }
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
