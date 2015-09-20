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
    BiomeMap::BiomeMap(Lua::Thread& luaThread)
        :luaThread_(luaThread)
    {}

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

        std::string biomeName;

        luaThread_.doWithState([&biomeName, position](lua_State* L) {
                lua_getglobal(L, "tlsd");
                lua_getfield(L, -1, "biomes");
                lua_getfield(L, -1, "get_biome_at");

                lua_pushnumber(L, position.getX());
                lua_pushnumber(L, position.getY());

                if (lua_pcall(L, 2, 1, 0) != 0)
                {
                    throw Error(
                        std::string("Error calling tlsd.biomes.get_biome_at : ") +
                        lua_tostring(L, -1)
                    );
                }

                if (!lua_isstring(L, -1))
                {
                    throw Error("tlsd.biomes.get_biome_at did not return a string");
                }

                biomeName = lua_tostring(L, -1);
                lua_pop(L, -1);
            });

        if (biomeName == "mountain")
        {
            return mountainBiome_;
        }
        else if (biomeName == "desert")
        {
            return desertBiome_;
        }
        else
        {
            return plainBiome_;
        }
    }

}
