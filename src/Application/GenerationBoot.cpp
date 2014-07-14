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

#include "GenerationBoot.h"

#include "Application.h"

#include <iostream> // TODO remove ?

namespace Application
{
    void GenerationBoot::cleanUp()
    {
        if (generationSystem_ != NULL)
        {
            generationSystem_->unregisterListeners(
                getApplication().getEventManager().getListenerRegister()
            );
            delete generationSystem_;
        }
    }

    void GenerationBoot::start()
    {
        // TODO should this manual generation remain ?
        // I think it should be in an event.
        World::Generation::ChunkGenerator generator(
            getApplication().getWorld(),
            getApplication().getEcsWorld(),
            42
        );

        // for (int i = -1; i <= 1; i++)
        // {
        //     for (int j = -1; j <= 1; j++)
        //     {
        //         generator.generateChunk(i, j);
        //     }
        // }
        generator.generateChunk(0, 0);

        std::cout << "[Generation]: Base generated" << std::endl;

        // TODO Change world seed at each run :-)
        generationSystem_ =
            new World::Generation::ChunkGenerationSystem(
                getApplication().getEcsWorld(),
                generator
            );

        generationSystem_->registerListeners(
            getApplication().getEventManager().getListenerRegister()
        );

        std::vector<Threading::ThreadableInterface*> threadables;
        threadables.push_back(generationSystem_);

        setThread(new Threading::Thread(threadables, 1));
        getThread().start();
        finishBoot();
    }
}
