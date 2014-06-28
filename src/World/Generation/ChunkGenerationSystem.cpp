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

#include "ChunkGenerationSystem.h"
#include "ChunkGenerationListener.h"

namespace World
{
    namespace Generation
    {
        ChunkGenerationSystem::ChunkGenerationSystem(
            Threading::ConcurrentRessource<Ecs::World>& world,
            ChunkGenerator chunkGenerator
        ): Ecs::System(world),
           chunkGenerator_(chunkGenerator)
        {
            Threading::createChannel<Geometry::Vec2Di>(
                channelInput_,
                channelOutput_
            );
            listener_ = new ChunkGenerationListener(channelInput_);
        }

        ChunkGenerationSystem::~ChunkGenerationSystem()
        {
            delete listener_;
        }

        void ChunkGenerationSystem::run()
        {
            while (!channelOutput_.isEmpty())
            {
                Geometry::Vec2Di pos;
                channelOutput_ >> pos;

                for (int i = -1; i <= 1; i++)
                {
                    for (int j = -1; j <= 1; j++)
                    {
                        chunkGenerator_.generateChunk(pos.getX() + i, pos.getY() + j);
                    }
                }

                for (int j = -3; j <= 3; j++)
                {
                    chunkGenerator_.removeChunk(pos.getX() - 3, pos.getY() + j);
                    chunkGenerator_.removeChunk(pos.getX() + 3, pos.getY() + j);

                    if (j != -3 && j != 3)
                    {
                        chunkGenerator_.removeChunk(pos.getX() + j, pos.getY() - 3);
                        chunkGenerator_.removeChunk(pos.getX() + j, pos.getY() + 3);
                    }
                }
            }
        }

        void ChunkGenerationSystem::registerListeners(Event::ListenerRegister& reg)
        {
            reg.put(
                Input::PlayerPositionChangedEvent::Type,
                listener_
            );
        }

        void ChunkGenerationSystem::unregisterListeners(Event::ListenerRegister& reg)
        {
            reg.remove(listener_);
        }
    }
}
