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

#ifndef WORLD_GENERATION_CITY_END_NODE_QUERY_INSERTER_H
#define WORLD_GENERATION_CITY_END_NODE_QUERY_INSERTER_H

#include "QueryInserterInterface.h"

#include "../../../Graph/PlanarGraph.h"

namespace World
{
    namespace Generation
    {
        namespace City
        {
            class EndNodeQueryInserter: public QueryInserterInterface
            {
            public:
                EndNodeQueryInserter(const Graph::PlanarNode& endNode):
                    endNode_(endNode)
                {}

                virtual Graph::PlanarEdge insert(const RoadQuery& query, Graph::PlanarGraph& graph);

                virtual bool mustCreateBranch()
                {
                    return false;
                }

            private:
                Graph::PlanarNode endNode_;
            };
        }
    }
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
