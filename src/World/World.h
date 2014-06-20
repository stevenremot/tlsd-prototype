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

#ifndef WORLD_WORLD_H
#define WORLD_WORLD_H

#include <map>
#include <stdexcept>

#include "Chunk.h"
#include "BiomeMap.h"
#include "../Geometry/Vec2D.h"

namespace World
{
    /**
     * Represents the world with its different generation states.
     *
     * TODO implement
     */
    class World
    {
    public:
        static const unsigned int ChunkSize;

        /**
         * Return the chunk at indexes (x, y)
         *
         * @param[in] x
         * @param[in] y
         * @param[out] chunk
         *
         * @return true if there is a chunk at index (x, y),
         *         false otherwise
         *
         * Be sure to check the return value before using the result.
         */
        bool getChunk(int x, int y, Chunk& chunk)
        {
            try
            {
                chunk = chunks_.at(Geometry::Vec2Di(x, y));
                return true;
            }
            catch (const std::out_of_range& e)
            {
                return false;
            }
        };

        void setChunk(int x, int y, const Chunk& chunk)
        {
            chunks_[Geometry::Vec2Di(x, y)] = chunk;
        }

        void setBiomeMap(const BiomeMap& biomeMap)
        {
            biomeMap_ = biomeMap;
        }

        /**
         * Return the biome at the given location
         *
         * @throw UninitializedCoefficientsException
         */
        BiomeInterface& getBiome(float x, float y);

        BiomeMap& getBiomeMap() { return biomeMap_; };
        const BiomeMap& getBiomeMap() const { return biomeMap_; };

    private:
        std::map<Geometry::Vec2Di, Chunk> chunks_;
        BiomeMap biomeMap_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
