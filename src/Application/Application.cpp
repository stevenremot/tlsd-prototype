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

#include "Application.h"

#include <iostream>

namespace Application
{
    Application::Application(const Random::Seed& seed, Event::EventManager& eventManager):
        vm_(),
        ecsWorld_(new Ecs::World(eventManager.getEventQueue())),
        eventManager_(eventManager),
        world_(),
        seed_(seed),
        running_(false)
    {
    }

    void Application::start()
    {
        runBoot(0);
    }

    void Application::runBoot(unsigned int bootIndex)
    {
        if (bootIndex < booters_.size())
        {
            booters_.at(bootIndex)->start(
                [this, bootIndex]() {
                    this->runBoot(bootIndex + 1);
                }
            );
        }
        else
        {
            startLoop();
        }
    }

    void Application::startLoop()
    {
        std::unique_ptr<Lua::Thread> intepreter = vm_.createThread();
        running_ = true;
        while (running_)
        {
            std::cout << ">> ";
            if (!std::cin.eof())
            {
                char command[256];
                std::cin.getline(command, sizeof(command));

                try
                {
                    intepreter->doString(command);
                }
                catch(const Lua::Thread::CodeError& e)
                {
                    std::cout << "Error : " << e.what() << std::endl;
                }
            }
        }

    }

    void Application::call(const Event::Event& event)
    {
        running_ = false;
    }

    const Random::Seed& Application::getSeed() const
    {
        return seed_;
    }
}
