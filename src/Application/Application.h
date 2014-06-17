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
#include "../Event/EventListenerInterface.h"
#include "../Ecs/World.h"
#include "../World/World.h"
#include "EventBoot.h"

namespace Application
{
    /**
     * Class in charge of launching the game
     */
    class Application : public Event::EventListenerInterface
    {
    public:
        Application();

        ~Application()
        {
            if (animationThread_ != NULL)
            {
                delete graphicsThread_;
                delete generationThread_;
                delete updateThread_;
                delete characterThread_;
                delete animationThread_;
            }
        }

        void start();


        virtual void call(const Event::Event& event);

        Event::EventManager& getEventManager()
        {
            return eventBoot_.getEventManager();
        }

        friend void applicationEventBootCallback(Application& application, BootInterface& eventBoot);

    private:
        EventBoot eventBoot_;
        Threading::Thread* graphicsThread_;
        Threading::Thread* updateThread_;
        Threading::Thread* generationThread_;
        Threading::Thread* characterThread_;
        Threading::Thread* animationThread_;
        Ecs::World ecsWorld_;
        World::World world_;
        bool running_;

        void setupGraphicsThread();
        void setupAnimationThread();
        void setupUpdateThread();
        void setupGenerationThread();
        void setupCharacterThread();
        void startLoop();
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
