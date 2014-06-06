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

#ifndef APPLICATION_APPLICATION_H
#define APPLICATION_APPLICATION_H

#include "../Threading/Thread.h"
#include "../Event/EventManager.h"
#include "../Ecs/World.h"
#include "../World/World.h"

namespace Application
{
    /**
     * Class in charge of launching the game
     */
    class Application
    {
    public:
        Application():
            eventThread_(NULL),
            graphicsThread_(NULL),
            generationThread_(NULL),
            eventManager_(),
            ecsWorld_(eventManager_.getEventQueue()),
            world_()
        {}

        ~Application()
        {
            if (eventThread_ != NULL)
            {
                delete eventThread_;
                delete graphicsThread_;
                delete generationThread_;
            }
        }

        void start();

    private:
        Threading::Thread* eventThread_;
        Threading::Thread* graphicsThread_;
        Threading::Thread* generationThread_;
        Event::EventManager eventManager_;
        Ecs::World ecsWorld_;
        World::World world_;

        void setupEventThread();
        void setupGraphicsThread();
        void setupGenerationThread();
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
