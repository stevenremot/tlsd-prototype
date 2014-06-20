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

#include "../Event/EventListenerInterface.h"
#include "../Threading/ConcurrentRessource.h"
#include "../Ecs/World.h"
#include "../World/World.h"
#include "EventBoot.h"
#include "GraphicsBoot.h"
#include "UpdateBoot.h"
#include "GenerationBoot.h"
#include "CharacterBoot.h"
#include "AnimationBoot.h"

namespace Application
{
    /**
     * Class in charge of launching the game
     */
    class Application : public Event::EventListenerInterface
    {
    public:
        Application();

        void start();


        virtual void call(const Event::Event& event);

        Event::EventManager& getEventManager()
        {
            return eventBoot_.getEventManager();
        }

        Threading::ConcurrentRessource<Ecs::World>& getEcsWorld()
        {
            return ecsWorld_;
        }

        World::World& getWorld()
        {
            return world_;
        }

        friend void applicationEventBootCallback(Application& application, BootInterface& eventBoot);
        friend void applicationGraphicsBootCallback(Application& application, BootInterface& graphicsBoot);
        friend void applicationUpdateBootCallback(Application& application, BootInterface& graphicsBoot);
        friend void applicationGenerationBootCallback(Application& application, BootInterface& graphicsBoot);
        friend void applicationCharacterBootCallback(Application& application, BootInterface& graphicsBoot);
        friend void applicationAnimationBootCallback(Application& application, BootInterface& graphicsBoot);

    private:
        EventBoot eventBoot_;
        Threading::ConcurrentRessource<Ecs::World> ecsWorld_;
        World::World world_;
        GraphicsBoot graphicsBoot_;
        UpdateBoot updateBoot_;
        GenerationBoot generationBoot_;
        CharacterBoot characterBoot_;
        AnimationBoot animationBoot_;
        bool running_;

        void startLoop();
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
