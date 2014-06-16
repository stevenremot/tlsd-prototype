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

namespace World
{

    void BiomeMap::addCityPolygon(const Geometry::Polygon2D& cityPolygon)
        {
            cityPolygons_.push_back(cityPolygon);
            cityPolygonsExtended_.push_back(cityPolygon.offset(static_cast<float>(World::ChunkSize) / std::sqrt(2.0))[0]);
        }


    BiomeInterface& BiomeMap::getBiome(const Geometry::Vec2Df& position)
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

        float chunkSize = World::ChunkSize;
        // Getting the position in the chunk
        float x = position.getX()-chunkSize/2;
        float y = position.getY()-chunkSize/2;

        int i = floor(x/chunkSize);
        int j = floor(y/chunkSize); 

        float x0 = x-i*chunkSize;
        float y0 = y-j*chunkSize;

        float n00, n01, n10, n11;
        // Computing the Perlin noise interpolation
        try
        {
            n00 = perlinCoefs_.at(Geometry::Vec2Di(i,j)).dot(Geometry::Vec2Df(x0,y0));
            n10 = perlinCoefs_.at(Geometry::Vec2Di(i+1,j)).dot(Geometry::Vec2Df(x0-chunkSize,y0));
            n01 = perlinCoefs_.at(Geometry::Vec2Di(i,j+1)).dot(Geometry::Vec2Df(x0,y0-chunkSize));
            n11 = perlinCoefs_.at(Geometry::Vec2Di(i+1,j+1)).dot(Geometry::Vec2Df(x0-chunkSize,y0-chunkSize));
        }
        catch(const std::out_of_range& e)
        {
            throw UninitializedCoefficientsException();
        }

        float xNorm = x0/chunkSize;
        float yNorm = y0/chunkSize;

        float interpolantX = xNorm*xNorm*xNorm*(xNorm*(xNorm*6-15)+10);
        float interpolantY = yNorm*yNorm*yNorm*(yNorm*(yNorm*6-15)+10);

        float nx0 = n00*(1-interpolantX)+n10*interpolantX;
        float nx1 = n01*(1-interpolantX)+n11*interpolantX;

        float nxy = nx0*(1-interpolantY)+nx1*interpolantY;

        // Threshold of the noise value
        // TODO externalize
        if (nxy>0.7)
        {
            return mountainBiome_;
        }
        else
        {
            return plainBiome_;
        }

    }

}
