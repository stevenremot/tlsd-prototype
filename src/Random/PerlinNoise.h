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

#ifndef RANDOM_PERLIN_NOISE_H
#define RANDOM_PERLIN_NOISE_H

#include <map>

#include "../Geometry/Vec2D.h"

namespace Random
{
    /**
     * Implements algorithms for perlin noise computation.
     */
    class PerlinNoise
    {
    public:
        /**
         * This exception is raised when trying to calculate the noise value
         * when the coefficients are not initialized
         */
        class UninitializedCoefficientsException: public std::exception
        {
        public:
            const char* what() const throw()
            {
                return "Trying to get perlin noise with uninitialized coefficients.";
            }
        };

        PerlinNoise();
        PerlinNoise(const PerlinNoise&) = delete;
        /* PerlinNoise& operator=(const PerlinNoise&) = delete; */

        /**
         * Set the perlin noise coefficient at the given position.
         *
         * @param position
         * @param coefficient
         *
         * @return itself
         */
        PerlinNoise& setCoefficient(
            const Geometry::Vec2Di& position,
            const Geometry::Vec2Df& coefficient
        );

        /**
         * Return true if there is a coefficient set for this position.
         */
        bool hasCoefficient(const Geometry::Vec2Di& position) const;

        /**
         *Compute the perlin noise at the given position.
         *
         * @param position
         *
         * @return The perlin noise coefficient
         */
        float computeAt(const Geometry::Vec2Df& position) const;

    private:
        std::map<Geometry::Vec2Di, Geometry::Vec2Df> coefficients_;
    };
}

#endif
