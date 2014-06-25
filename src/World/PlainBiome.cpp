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

#include "PlainBiome.h"

namespace World
{
    const BiomeInterface::Type PlainBiome::Type = "PlainBiome";

    float PlainBiome::transformCoefficient(float coefficient)
    {
        return (coefficient + 1.0) * 15.0;
    }

    Graphics::Color PlainBiome::getColor()
    {
        return Graphics::Color(0, 1, 0);
    }

    const Generation::TreeParameters PlainBiome::getTreeParameters()
    {
        std::vector<Graphics::Color> trunkMin;
        trunkMin.push_back(Graphics::Color(0.5, 0.25, 0.15));
        trunkMin.push_back(Graphics::Color(0.5, 0.25, 0.15));
        std::vector<Graphics::Color> trunkMax;
        trunkMax.push_back(Graphics::Color(0.7, 0.35, 0.25));
        trunkMax.push_back(Graphics::Color(0.7, 0.35, 0.25));
        std::vector<Graphics::Color> leavesMin;
        leavesMin.push_back(Graphics::Color(0.9, 0.8, 0.8));
        leavesMin.push_back(Graphics::Color(0.15, 0.7, 0.15));
        std::vector<Graphics::Color> leavesMax;
        leavesMax.push_back(Graphics::Color(1.0, 0.9, 0.9));
        leavesMax.push_back(Graphics::Color(0.25, 0.9, 0.25));
        return Generation::TreeParameters(
            4.0,
            6.0,
            2.0,
            3.0,
            8.0,
            12.0,
            8.0,
            12.0,
            -0.4,
            0.4,
            2,
            trunkMin,
            trunkMax,
            leavesMin,
            leavesMax
        );
    }
}
