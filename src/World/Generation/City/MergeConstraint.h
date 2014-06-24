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

#ifndef WORLD_GENERATION_CITY_MERGE_CONSTRAINT_H
#define WORLD_GENERATION_CITY_MERGE_CONSTRAINT_H

#include "RoadConstraintInterface.h"

namespace World
{
    namespace Generation
    {
        namespace City
        {
            /**
             * This constraint invalidates the road if it is similar
             * to another one.
             */
            class MergeConstraint: public RoadConstraintInterface
            {
            public:
                MergeConstraint(float radius, float deviation):
                    radius_(radius),
                    deviation_(deviation)
                {}

                virtual void insert(
                    RoadQuery& query,
                    const RoadNetwork& network
                );
            private:
                float radius_;
                float deviation_;
            };
        }
    }
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
