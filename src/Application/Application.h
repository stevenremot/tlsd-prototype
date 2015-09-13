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
#include "../Lua/Vm.h"
#include "../Random/NumberGenerator.h"

#include "BootInterface.h"

namespace Application
{
    /**
     * Class in charge of launching the game
     */
    class Application : public Event::EventListenerInterface
    {
    public:
        Application(const Random::Seed& seed, Event::EventManager& enventManager);

        void start();


        virtual void call(const Event::Event& event);

        Event::EventManager& getEventManager()
        {
            return eventManager_;
        }

        Threading::ConcurrentRessource<Ecs::World>& getEcsWorld()
        {
            return ecsWorld_;
        }

        World::World& getWorld()
        {
            return world_;
        }

        Application& addBooter(BootInterface* booter)
        {
            booters_.push_back(std::unique_ptr<BootInterface>(booter));
            return *this;
        }

        const Random::Seed& getSeed() const;

        Lua::Vm& getVm()
        {
            return vm_;
        }

    private:
        Lua::Vm vm_;
        // EventBoot eventBoot_;
        Threading::ConcurrentRessource<Ecs::World> ecsWorld_;
        Event::EventManager& eventManager_;
        World::World world_;
        const Random::Seed seed_;

        std::vector< std::unique_ptr<BootInterface> > booters_;

        bool running_;

        void runBoot(unsigned int bootIndex);

        void startLoop();
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
