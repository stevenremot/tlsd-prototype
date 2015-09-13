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

#include "BiomeMap.h"
#include "World.h"
#include "../Geometry/Vec2D.h"
#include "../Geometry/Polygon2D.h"

using Geometry::Vec2Df;

namespace World
{
    void BiomeMap::setPerlinCoef(int x, int y, const std::vector<Vec2Df>& perlinCoef)

    {
        humidityNoise_.setCoefficient(Geometry::Vec2Di(x, y), perlinCoef[0]);
        temperatureNoise_.setCoefficient(Geometry::Vec2Di(x, y), perlinCoef[1]);
    }

    void BiomeMap::addCityPolygon(const Geometry::Polygon2D& cityPolygon)
    {
        cityPolygons_.push_back(cityPolygon);
        cityPolygonsExtended_.push_back(cityPolygon.offset(static_cast<float>(World::ChunkSize) / std::sqrt(2.0))[0]);
    }

    BiomeInterface& BiomeMap::getBiome(const Vec2Df& position)
    {
        unsigned int length = cityPolygonsExtended_.size();
        // Checking the position of the cities
        for (unsigned int i = 0; i < length; i++)
        {
            if (cityPolygonsExtended_[i].contains(position))
            {
                return cityBiome_;
            }
        }

        Vec2Df noisePos = (position / World::ChunkSize) - Vec2Df(0.5, 0.5);
        float nxy1 = humidityNoise_.computeAt(noisePos);
        float nxy2 = temperatureNoise_.computeAt(noisePos);

        // Threshold of the noise value
        // TODO externalize
        if (nxy1 >= 0 && nxy2 < 0)
        {
            return mountainBiome_;
        }
        else if (nxy1 < 0 && nxy2 < 0)
        {
            return desertBiome_;
        }
        else
        {
            return plainBiome_;
        }

    }

}
