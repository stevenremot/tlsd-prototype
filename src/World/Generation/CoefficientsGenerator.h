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

#ifndef WORLD_COEFFICIENTS_GENERATOR_H
#define WORLD_COEFFICIENTS_GENERATOR_H

#include <vector>

#include "../../Random/NumberGenerator.h"
#include "../GroundCoefficients.h"
#include "../../Geometry/Vec2D.h"

namespace World
{

    namespace Generation
    {
        /*
         * Generate 3 octaves of coefficients for the simplex noise
         */
        GroundCoefficients generateGroundCoefficients(Random::NumberGenerator& rng);
    }

}

#endif
