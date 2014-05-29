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

#ifndef WORLD_GROUND_COEFFICIENTS_H
#define WORLD_GROUND_COEFFICIENTS_H

#include <exception>

#include "../Geometry/Vec2D.h"

namespace World
{
    /**
     * Coefficients used for the ground generation
     *
     * Contains three octaves of coefficients used for generating
     * the different levels of details
     */
    class GroundCoefficients
    {
    public:
        /**
         * This exception is raised when positions and octave are
         * not correct
         */
        class BadParametersException: public std::exception
        {
        public:
            const char* what() const throw()
            {
                return "Trying to access an unexisting position or unexisting octave";
            }
        };

        /**
         * Return the coefficient in the given octave at the given position
         *
         * @throw BadParametersException when the parameters are not correct
         */
        float getCoefficient(int octave, int i, int j) const;

        /**
         * Set the given coefficient at the given position in the given octave
         *
         * @throw BadParametersException when the parameters are not correct
         */
        void setCoefficient(int octave, int i, int j, float coefficient);

    private:
        float firstOctave_;
        float secondOctave_[2][2];
        float thirdOctave_[4][4];
        void checkValidity(int octave, int i, int j) const;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
