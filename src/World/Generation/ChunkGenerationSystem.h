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

#ifndef WORLD_GENERATION_CHUNK_GENERATION_SYSTEM_H
#define WORLD_GENERATION_CHUNK_GENERATION_SYSTEM_H

#include "../../Ecs/System.h"
#include "../../Threading/ThreadableInterface.h"
#include "../../Threading/Channel.h"
#include "../../Event/ListenerRegister.h"
#include "../../Geometry/Vec2D.h"
#include "../../Input/PlayerPositionChangedEvent.h"
#include "ChunkGenerator.h"

namespace World
{
    namespace Generation
    {
        class ChunkGenerationSystem: public Ecs::System,
                                     public Threading::ThreadableInterface
        {
        public:
            typedef Threading::ChannelInput<Geometry::Vec2Di> CommandQueue;

            ChunkGenerationSystem(
                Ecs::World& world,
                ChunkGenerator chunkGenerator
            ): Ecs::System(world),
               chunkGenerator_(chunkGenerator)
            {
                Threading::createChannel<Geometry::Vec2Di>(
                    channelInput_,
                    channelOutput_
                );
            }

            CommandQueue& getCommandQueue()
            {
                return channelInput_;
            }

            void registerListeners(Event::ListenerRegister& reg);

            virtual void call();

        private:
            CommandQueue channelInput_;
            Threading::ChannelOutput<Geometry::Vec2Di> channelOutput_;
            ChunkGenerator chunkGenerator_;
        };
    }
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
