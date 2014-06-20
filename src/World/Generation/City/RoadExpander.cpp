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

#include "RoadExpander.h"

namespace World
{
    namespace Generation
    {
        namespace City
        {
            bool RoadExpander::expand()
            {
                if (branchRequests_.empty())
                {
                    return false;
                }

                QueryCreator::QueryCollection queries =
                    queryCreator_.createQueries(branchRequests_.front());
                branchRequests_.pop_front();

                for (unsigned int i = 0; i < queries.size(); i++)
                {
                    RoadQuery& query = queries[i];

                    for (unsigned int j = 0; j < constraints_.size(); j++)
                    {
                        RoadConstraintInterface& constraint = *constraints_[j];
                        constraint.insert(query, network_);
                        if (query.getState() == RoadQuery::CancelledState)
                            break;
                    }

                    if (query.getState() != RoadQuery::CancelledState)
                    {
                        Graph::PlanarEdge edge =
                            query.getInserter().insert(query, network_.getGraph());

                        if (query.getInserter().mustCreateBranch())
                        {
                            addBranchRequest(BranchRequest(
                                                 edge.getOtherNode(query.getOriginNode()),
                                                 edge
                                             ));
                        }
                    }
                }

                return true;
            }
        }
    }
}
