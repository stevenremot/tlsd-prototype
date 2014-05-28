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

#ifndef WORLD_GENERATION_CITY_ROAD_EXPANDER_H
#define WORLD_GENERATION_CITY_ROAD_EXPANDER_H

#include "../../RoadNetwork.h"
#include "BranchRequest.h"
#include "QueryCreator.h"
#include "RoadConstraintInterface.h"

#include <vector>
#include <list>

namespace World
{
    namespace Generation
    {
        namespace City
        {
            /**
             * Class in charge of expanding a road network
             */
            class RoadExpander
            {
            public:
                RoadExpander(QueryCreator queryCreator, const RoadNetwork& network):
                    queryCreator_(queryCreator),
                    network_(network)
                {}

                ~RoadExpander()
                {
                    for (unsigned int i = 0; i < constraints_.size(); i++)
                    {
                        delete constraints_[i];
                    }
                }

                /**
                 * Add a branch request to process in the end of the queue.
                 */
                void addBranchRequest(const BranchRequest& request)
                {
                    branchRequests_.push_back(request);
                }

                /**
                 * Add the road constraint at the end of the current constraints
                 */
                void addRoadConstraint(RoadConstraintInterface* constraint)
                {
                    constraints_.push_back(constraint);
                }

                /**
                 * Expand the road network given in parameter
                 *
                 * @return true if there were branch request, false otherwise
                 */
                bool expand();

                RoadNetwork& getRoadNetwork() { return network_; }

            private:
                QueryCreator queryCreator_;
                std::vector<RoadConstraintInterface*> constraints_;
                std::list<BranchRequest> branchRequests_;
                RoadNetwork network_;
            };
        }
    }
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
