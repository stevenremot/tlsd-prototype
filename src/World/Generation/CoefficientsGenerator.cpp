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

#include "CoefficientsGenerator.h"

namespace World
{
    namespace Generation
    {
        GroundCoefficients generateGroundCoefficients(Random::NumberGenerator& rng)
        {

            GroundCoefficients groundCoefficients;
            float n;
            // Generate the first octave
            n = rng.getUniform(-1.0, 1.0);
            groundCoefficients.setCoefficient(1, 0, 0, n);
            // Generate the second octave
            for (unsigned int i = 0; i < 2; i++)
            {
                for (unsigned int j = 0; j < 2; j++)
                {
                    n = rng.getUniform(-1.0, 1.0);
                    groundCoefficients.setCoefficient(
                        2,
                        i,
                        j,
                        n
                    );
                }
            }
            // Generate the third octave
            for (unsigned int i = 0; i < 4; i++)
            {
                for (unsigned int j = 0; j < 4; j++)
                {
                    n = rng.getUniform(-1.0, 1.0);
                    groundCoefficients.setCoefficient(
                        3,
                        i,
                        j,
                        n
                    );
                }
            }
            return groundCoefficients;
        }
    }
}
