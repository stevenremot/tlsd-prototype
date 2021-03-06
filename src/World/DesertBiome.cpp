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

#include "DesertBiome.h"

namespace World
{
    const BiomeInterface::Type DesertBiome::Type = "DesertBiome";

    float DesertBiome::transformCoefficient(float coefficient)
    {
        return (coefficient + 1.0) * 30.0;
    }

    Graphics::Color DesertBiome::getColor()
    {
        return Graphics::Color(1.0, 0.8, 0.0);
    }

    const Generation::TreeParameters DesertBiome::getTreeParameters()
    {
        std::vector<Graphics::Color> trunkMin;
        trunkMin.push_back(Graphics::Color(0.8, 0.55, 0.45));
        std::vector<Graphics::Color> trunkMax;
        trunkMax.push_back(Graphics::Color(1, 0.75, 0.55));
        std::vector<Graphics::Color> leavesMin;
        leavesMin.push_back(Graphics::Color(0.55, 0.7, 0.15));
        std::vector<Graphics::Color> leavesMax;
        leavesMax.push_back(Graphics::Color(0.65, 0.9, 0.25));
        return Generation::TreeParameters(
            3.0,
            6.0,
            1.0,
            2.0,
            2.0,
            3.2,
            6.0,
            10.0,
            -2.5,
            2.5,
            1,
            "cubique",
            trunkMin,
            trunkMax,
            leavesMin,
            leavesMax
        );
    }
}
