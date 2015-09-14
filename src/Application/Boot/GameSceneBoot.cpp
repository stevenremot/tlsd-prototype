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

#include "GameSceneBoot.h"

#include <iostream>

#include "../Application.h"


// TODO includes for group, remove later
#include "../../Character/GroupComponent.h"
#include "../../Character/EntityCreator.h"
#include "../../Character/Statistics.h"

// TODO for ai, remove later
#include "../../AI/AiComponent.h"
#include "../../AI/BasicAiModule.h"
#include "../../AI/MemoryComponent.h"
#include "../../AI/Sensor/SensorComponent.h"
#include "../../AI/SubSystems/TargetingComponent.h"
#include "../../AI/Sensor/SightSensor.h"
#include "../../tests/stateMachine.h"
#include "../../AI/SubSystems/NavigationSubsystem.h"

namespace Application
{
    GameSceneBoot::GameSceneBoot(Application& application): application_(application)
    {}

    void GameSceneBoot::start(Callback callback)
    {
        {
            Threading::ConcurrentWriter<Ecs::World> world = application_.getEcsWorld().getWriter();
            auto& eventManager = application_.getEventManager();

            Ecs::Entity group = world->createEntity();
            Character::GroupComponent* groupComponent = new Character::GroupComponent();
            world->addComponent(group, groupComponent);

            Character::createPlayer(
            world,
            Geometry::Vec3Df(150,150,150),
            Geometry::Vec3Df(0,0,0),
            Character::Statistics(100, 25, 20, 5),
            group,
            eventManager.getEventQueue()
            );

            Ecs::Entity badGuy = Character::createCharacter(
            world,
            Geometry::Vec3Df(160, 160, 150),
            Geometry::Vec3Df(0, 0, 0),
            Character::Statistics(70, 20, 20, 5),
            group,
            eventManager.getEventQueue()
            );

            AI::AiComponent* aiComponent = new AI::AiComponent(
            badGuy,
            eventManager.getEventQueue()
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

        callback();
    }
}
