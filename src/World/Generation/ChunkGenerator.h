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

#ifndef WORLD_GENERATION_CHUNK_GENERATOR_H
#define WORLD_GENERATION_CHUNK_GENERATOR_H

#include <vector>

#include "../World.h"
#include "../../Ecs/World.h"
#include "../../Random/NumberGenerator.h"
#include "../../Threading/ConcurrentRessource.h"
#include "../SimpleTree.h"

namespace World
{
    namespace Generation
    {
        /**
         * Class in charge of generating chunks for a world
         *
         * This is the main entry point for procedural generation.
         */
        class ChunkGenerator
        {
        public:
            ChunkGenerator(
                World& world,
                Threading::ConcurrentRessource<Ecs::World>& ecsWorld,
                Random::Seed worldSeed
            ): world_(world),
               ecsWorld_(ecsWorld),
               worldSeed_(worldSeed)
            {}

            /**
             * Generate a chunk and load it in the ECS.
             */
            void generateChunk(int x, int y);

            /**
             * Cancel the generation of the chunk
             */
            void unGenerateChunk(int x, int y);

            /**
             * Totally forget about the chunk in x, y
             */
            void removeChunk(int x, int y);

        private:
            World& world_;
            Threading::ConcurrentRessource<Ecs::World>& ecsWorld_;
            Random::Seed worldSeed_;

            void prepareChunk(int x, int y);

            /**
             * Generate a city in the chunk (x, y)
             */
            void generateCity(int x, int y, Random::NumberGenerator& rng);

            /**
             * Generate trees in the chunk (x, y)
             *
             * @param[in] x
             * @param[in] y
             * @param[in] rng
             * @param[out] positions
             * @param[out] trees
             */
            void generateTrees(int x, int y, Random::NumberGenerator& rng, std::vector<Geometry::Vec3Df>& position, std::vector<SimpleTree*>& trees);
            Random::Seed getChunkSeed(int x, int y);

            void insertDescriptor(
                Core::SharedPtr<Ecs::EntityDescriptor>& descriptor,
                int defaultI,
                int defaultJ
            );
        };
    }
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
