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

#ifndef WORLD_GENERATION_CITY_QUERY_INSERTER_INTERFACE_H
#define WORLD_GENERATION_CITY_QUERY_INSERTER_INTERFACE_H

#include "../../../Graph/PlanarGraph.h"

namespace World
{
    namespace Generation
    {
        namespace City
        {
            class RoadQuery;

            /**
             * An interface for objects that can insert a query in a graph.
             */
            class QueryInserterInterface
            {
            public:
                virtual ~QueryInserterInterface() {};


                /**
                 * Insert the query in the graph
                 *
                 * @return the node at the end of the query
                 */
                virtual Graph::PlanarEdge insert(
                    const RoadQuery& query,
                    Graph::PlanarGraph& graph
                ) = 0;

                /**
                 * Return true if a branch must be created after the insertion
                 */
                virtual bool mustCreateBranch() = 0;
            };
        }
    }
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
