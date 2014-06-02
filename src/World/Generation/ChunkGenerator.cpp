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

#include "ChunkGenerator.h"
#include "../EntityCreator.h"
#include "CoefficientsGenerator.h"

namespace World
{
    namespace Generation
    {

        Random::Seed ChunkGenerator::getChunkSeed(int x, int y)
        {
            // Use more robust seed generator (z-order?)
            return worldSeed_ + static_cast<Random::Seed>(x + y * y);
        }

        void ChunkGenerator::generateChunk(int x, int y)
        {
            Chunk currentChunk;

            if (world_.getChunk(x, y, currentChunk) &&
                currentChunk.getState() == Chunk::GeneratedState) {
                return;
            }

            for (int i = -1; i < 1; i++)
            {
                for (int j = -1; j < 1; j++)
                {
                    prepareChunk(x + i, y + j);
                }
            }

            world_.getChunk(x, y, currentChunk);

            Chunk::EntityCollection finalEntities;

            finalEntities.push_back(createGround(world_, x, y, ecsWorld_));

            currentChunk.setFinalEntities(finalEntities);
            currentChunk.setState(Chunk::GeneratedState);
            world_.setChunk(x, y, currentChunk);
        }

        void ChunkGenerator::prepareChunk(int x, int y)
        {
            Chunk currentChunk;
            if (world_.getChunk(x, y, currentChunk) &&
                currentChunk.getState() != Chunk::NotLoadedState)
            {
                return;
            }

            Random::NumberGenerator rng(getChunkSeed(x, y));

            BiomeMap& biomeMap = world_.getBiomeMap();
            biomeMap.setPerlinCoef(x, y, generatePerlinCoefficient(rng));

            currentChunk.setCoefficients(generateGroundCoefficients(rng));

            currentChunk.setState(Chunk::PreparedState);
            world_.setChunk(x, y, currentChunk);
        }
    }
}
