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

#ifndef WORLD_BIOME_MAP_H
#define WORLD_BIOME_MAP_H

#include <map>
#include <vector>

#include "MountainBiome.h"
#include "CityBiome.h"
#include "PlainBiome.h"
#include "DesertBiome.h"

#include "../Lua/Thread.h"
#include "../Core/Error.h"

#include "../Geometry/Vec2D.h"
#include "../Geometry/Polygon2D.h"

#include "../Random/PerlinNoise.h"

namespace World
{
    /**
     * Handles the mapping between a position and a biome
     *
     */
    class BiomeMap
    {
    public:
        class Error: public Core::Error
        {
        public:
            Error(const std::string& errorMsg): Core::Error(errorMsg) {}
        };

        BiomeMap(Lua::Thread& luaThread);

        void addCityPolygon(const Geometry::Polygon2D& cityPolygon);
        /**
         * Returns the biome at the given position
         *
         * @throw UninitializedCoefficientsException
         */
        BiomeInterface& getBiome(const Geometry::Vec2Df& position);

        const std::vector<Geometry::Polygon2D>& getCityPolygons()
        {
            return cityPolygons_;
        }

    private:
        Lua::Thread& luaThread_;

        std::vector<Geometry::Polygon2D> cityPolygons_;
        std::vector<Geometry::Polygon2D> cityPolygonsExtended_;

        CityBiome cityBiome_;
        MountainBiome mountainBiome_;
        PlainBiome plainBiome_;
        DesertBiome desertBiome_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
