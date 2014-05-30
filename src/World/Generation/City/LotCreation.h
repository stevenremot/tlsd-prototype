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

#ifndef WORLD_GENERATION_CITY_LOT_CREATION_H
#define WORLD_GENERATION_CITY_LOT_CREATION_H

#include <vector>
#include <exception>

#include "../../../Geometry/Polygon2D.h"
#include "../../../Graph/PlanarPrimitive.h"
#include "../../../Random/NumberGenerator.h"

namespace World
{
    namespace Generation
    {
        namespace City
        {
            typedef std::vector<Geometry::Polygon2D> LotCollection;

            class WrongPrimitiveException: public std::exception
            {
                const char* what() const throw()
                {
                    return "Primitive is not a cycle.";
                }
            };

            /**
             * Divide a cycle in a number of lots that can contain buildings.
             *
             * Throw a WrongPrimitiveException if the provided primitive is not a cycle.
             *
             * @param cycle cycle to split
             * @param minimumRoadLength minimal length of roads
             * @param maximumRoadLength maximum length of roads after split
             * @param rng number generator
             */
            LotCollection createLots(
                const Graph::PlanarPrimitive& cycle,
                float minimumRoadLength,
                float maximumRoadLength,
                Random::NumberGenerator& rng
            );
        }
    }
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
