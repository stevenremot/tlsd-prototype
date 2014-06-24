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

#include "GroundCoefficients.h"

namespace World
{
    float GroundCoefficients::getCoefficient(int octave, int i, int j) const
    {
        checkValidity(octave,i,j);
        switch (octave)
        {
        case 1:
            return firstOctave_;
            break;
        case 2:
            return secondOctave_[i][j];
            break;
        default:
            // As coefficients have been checked before,
            // We are sure it is the third coefficient here.
            return thirdOctave_[i][j];
            break;
        }
    }

    void GroundCoefficients::setCoefficient(int octave, int i, int j, float coefficient)
    {
        checkValidity(octave,i,j);
        switch (octave)
        {
            case 1:
                firstOctave_ = coefficient;
                break;
            case 2:
                secondOctave_[i][j] = coefficient;
                break;
            case 3:
                thirdOctave_[i][j] = coefficient;
                break;
        }
    }

    void GroundCoefficients::checkValidity(int octave, int i, int j) const
    {
        if (octave>3 || octave<1 || i<0 || j<0)
        {
            throw BadParametersException();
        }

        else if (octave==2 && (i>1 || j>1))
        {
            throw BadParametersException();
        }

        else if (octave==3 && (i>3 || j>3))
        {
            throw BadParametersException();
        }
    }

}
