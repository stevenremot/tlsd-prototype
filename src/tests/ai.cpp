#include "ai.h"

#include <iostream>

#include "../Ecs/World.h"

#include <vector>

#include "../AI/AiComponent.h"
#include "../AI/Sensor/SightSensor.h"
#include "../AI/SubSystems/TargetingSubsystem.h"
#include "../AI/SubSystems/NavigationSubsystem.h"
#include "../AI/AiSystem.h"

#include "../Geometry/PositionComponent.h"
#include "../Geometry/Vec3D.h"

#include "../Physics/MovementComponent.h"
#include "../Physics/MovementSystem.h"

#include "../Threading/Thread.h"

using std::cout;
using std::endl;
using std::vector;

namespace AITest
{
    void testAI()
    {
        Ecs::World w = Ecs::World();
        // Create the unit with the ai module
        Ecs::Entity e1 = w.createEntity();
        AI::AiComponent* aiComponent = new AI::AiComponent(w);
        w.addComponent(e1, aiComponent);

        // Add a sight sensor
        AI::Sensor::SensorsManager& sensorsManager = aiComponent->getSensorsManager();
        //AI::Sensor::SightSensor::Type sightSensorType;
        sensorsManager.addSensor(AI::Sensor::SightSensor::Type);

        // Add navigation and targeting subsytems
        AI::Subsystem::SubSystemsManager& subsystemsManager = aiComponent->getSubsystemsManager();
        subsystemsManager.addSubsystem(AI::Subsystem::TargetingSubsystem::Type);
        subsystemsManager.addSubsystem(AI::Subsystem::NavigationSubSystem::Type);

        // Create an other unit
        Ecs::Entity e2 = w.createEntity();
        Geometry::PositionComponent* positionComponent = new Geometry::PositionComponent(Geometry::Vec3Df(0.f,200.f,0.0f));
        w.addComponent(e2, positionComponent);
        w.addComponent(e2, new Physics::MovementComponent(Geometry::Vec3Df(0.f,-20.f,0.0f)));

        // Create the systems for ai and movement
        AI::AiSystem aiSystem(w);
        Physics::MovementSystem movementSystem(w);

        vector<Threading::ThreadableInterface*> systems;
        systems.push_back(&aiSystem);
        systems.push_back(&movementSystem);

        Threading::Thread thread(systems, 1);
        thread.start();
        bool isRunning = true;
        while(isRunning)
        {
            isRunning = (positionComponent->getPosition().getY() > 0.f);
        }
        thread.stop();

    }
}
