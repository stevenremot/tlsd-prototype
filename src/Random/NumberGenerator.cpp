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

#include "NumberGenerator.h"

#include <ctime>
#include <cmath>

#include <iostream>

namespace Random
{
    Seed createSeed()
    {
        return std::time(NULL);
    }

    static const unsigned int RandomCoefficient = 3039177861;
    static const unsigned int RandMax = 1 << 31;

    Seed NumberGenerator::computeNextSeed() const
    {
        // Implementation using a linear congruential generator
        // Introduced by Borosh and Niederreiter
        return RandomCoefficient * currentSeed_ % RandMax;
    }

    float NumberGenerator::getUniform(float min, float max)
    {
        currentSeed_ = computeNextSeed();
        return (static_cast<float>(currentSeed_) / static_cast<float>(RandMax)) *
            (max - min) + min;
    }

    unsigned int NumberGenerator::getPoisson(unsigned int mean)
    {
        // Use implementation from Gabor noise article :
        // Procedural noise using sparse gabor convolution
        // By A. Lagae, S. Lefebvre, G. Drettakis, P. Dutré
        float g = std::exp(-static_cast<int>(mean));
        unsigned int em = 0;
        float t = getUniform();

        while (t > g)
        {
            em += 1;
            t *= getUniform();
        }

        return em;
    }
}
