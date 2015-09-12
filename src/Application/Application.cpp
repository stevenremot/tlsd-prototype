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

// TODO includes for group, remove later
#include "../Character/GroupComponent.h"
#include "../Character/EntityCreator.h"
#include "../Character/Statistics.h"

// TODO for ai, remove later
#include "../AI/AiComponent.h"
#include "../AI/BasicAiModule.h"
#include "../AI/MemoryComponent.h"
#include "../AI/Sensor/SensorComponent.h"
#include "../AI/SubSystems/TargetingComponent.h"
#include "../AI/Sensor/SightSensor.h"
#include "../tests/stateMachine.h"
#include "../AI/SubSystems/NavigationSubsystem.h"

// TODO for lua VM, remove later
#include "../Lua/Api/Random.h"

namespace Application
{
    void applicationEventBootCallback(Application& application, BootInterface& eventBoot)
    {
        application.graphicsBoot_.start();
    }

    void applicationGraphicsBootCallback(Application& application, BootInterface& graphicsBoot)
    {
        application.updateBoot_.start();
    }

    void applicationUpdateBootCallback(Application& application, BootInterface& graphicsBoot)
    {
        application.generationBoot_.start();
    }

    void applicationGenerationBootCallback(Application& application, BootInterface& graphicsBoot)
    {
        application.characterBoot_.start();
    }

    void applicationCharacterBootCallback(Application& application, BootInterface& graphicsBoot)
    {
        application.animationBoot_.start();
    }

    void applicationAnimationBootCallback(Application& application, BootInterface& graphicsBoot)
    {
        application.aiBoot_.start();
    }

    void applicationAiBootCallback(Application& application, BootInterface& aiBoot)
    {
        application.startLoop();
    }

    Application::Application(const Random::Seed& seed):
        vm_(),
        eventBoot_(applicationEventBootCallback, *this),
        ecsWorld_(new Ecs::World(eventBoot_.getEventManager().getEventQueue())),
        world_(),
        seed_(seed),
        graphicsBoot_(applicationGraphicsBootCallback, *this),
        updateBoot_(applicationUpdateBootCallback, *this),
        generationBoot_(applicationGenerationBootCallback, *this),
        characterBoot_(applicationCharacterBootCallback, *this),
        animationBoot_(applicationAnimationBootCallback, *this),
        aiBoot_(applicationAiBootCallback, *this),
        running_(false)
    {
        Lua::Api::Random::setup(vm_, seed);
    }

    void Application::start()
    {
        eventBoot_.start();
    }

    void Application::startLoop()
    {
        // TODO set z at 0, not 150
        {
            Threading::ConcurrentWriter<Ecs::World> world = ecsWorld_.getWriter();


            Ecs::Entity group = world->createEntity();
            Character::GroupComponent* groupComponent = new Character::GroupComponent();
            world->addComponent(group, groupComponent);

            Character::createPlayer(
                world,
                Geometry::Vec3Df(150,150,150),
                Geometry::Vec3Df(0,0,0),
                Character::Statistics(100, 25, 20, 5),
                group,
                eventBoot_.getEventManager().getEventQueue()
            );

            Ecs::Entity badGuy = Character::createCharacter(
                world,
                Geometry::Vec3Df(160, 160, 150),
                Geometry::Vec3Df(0, 0, 0),
                Character::Statistics(70, 20, 20, 5),
                group,
                eventBoot_.getEventManager().getEventQueue()
            );

            AI::AiComponent* aiComponent = new AI::AiComponent(
                badGuy,
                getEventManager().getEventQueue()
            );
            AI::Sensor::SensorComponent* sensorComponent =
                new AI::Sensor::SensorComponent(badGuy);

            AI::BasicAiModule* aiModule = new AI::BasicAiModule(StateMachineTest::Idle);
            StateMachineTest::setupStateMachine(*aiModule);
            aiComponent->setAiModule(aiModule);

            // Add a sight sensor
            AI::Sensor::SensorManager& sensorsManager = sensorComponent->getSensorsManager();
            sensorsManager.addSensor(AI::Sensor::SightSensor::Type);

            // Add navigation and targeting subsytems
            AI::Subsystem::SubSystemsManager& subsystemsManager = aiComponent->getSubsystemsManager();

            subsystemsManager.addSubsystem(AI::Subsystem::NavigationSubSystem::Type);

            world->addComponent(badGuy, new AI::MemoryComponent());
            world->addComponent(badGuy, sensorComponent);
            world->addComponent(badGuy, new AI::Subsystem::TargetingComponent());
            world->addComponent(badGuy, aiComponent);
        }

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
