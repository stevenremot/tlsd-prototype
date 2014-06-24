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

#include "MountainBiome.h"

namespace World
{
    const BiomeInterface::Type MountainBiome::Type = "MountainBiome";

    float MountainBiome::transformCoefficient(float coefficient)
    {
        return (coefficient+1.0)*25.0+150.0;
    }

    Graphics::Color MountainBiome::getColor()
    {
        return Graphics::Color(0.25,0.25,0.25);
    }

    const Generation::TreeParameters MountainBiome::getTreeParameters()
    {
        return Generation::TreeParameters(
            2.5,
            4.0,
            2.5,
            5.0,
            15.0,
            25.0,
            8.0,
            12.0,
            0,
            0,
            Graphics::Color(0.3,0.1,0.02),
            Graphics::Color(0.5,0.2,0.06),
            Graphics::Color(0,0.4,0),
            Graphics::Color(0.05,0.5,0.1)
        );
    }

}
