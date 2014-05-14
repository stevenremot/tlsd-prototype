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

#ifndef RANDOM_NUMBER_GENERATOR_H
#define RANDOM_NUMBER_GENERATOR_H

namespace Random
{
    /**
     * Random number generator seed
     */
    typedef unsigned int Seed;
    /**
     * Create a seed
     *
     * Uses an ever-changing value to generate a seed
     */
    Seed createSeed();

    /**
     * Class for generating random numbers.
     *
     * Using a base seed, a number generator can output various
     * random numbers.
     */
    class NumberGenerator
    {
    public:
        NumberGenerator()
        {
            currentSeed_ = createSeed();
        }

        NumberGenerator(Seed seed): currentSeed_(seed)
        {}

        // Copy operators
        NumberGenerator(const NumberGenerator& ng): currentSeed_(ng.currentSeed_)
        {}

        NumberGenerator& operator=(const NumberGenerator& ng)
        {
            currentSeed_ = ng.currentSeed_;
            return *this;
        }

        // Number generation methods

        /**
         * Return a random floating-point number between min and max
         */
        float getUniform(float min = 0.0, float max = 1.0);

        /**
         * Return a positive random number following a poisson distribution
         *
         * @param mean the mean of the poisson distribution
         */
        unsigned int getPoisson(unsigned int mean);

    private:
        Seed currentSeed_;

        Seed computeNextSeed() const;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
