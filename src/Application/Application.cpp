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

#include "../Graphics/Device.h"
#include "../Graphics/CloseDeviceEvent.h"
#include "../Graphics/Render/Scene.h"
#include "../Graphics/Render/RenderSystem.h"
#include "../Graphics/Render/RenderEvents.h"
#include "../Input/IrrlichtInputReceiver.h"
#include "../Input/Events.h"
#include "../Input/IrrlichtInputReceiver.h"
#include "../World/Generation/ChunkGenerationSystem.h"
#include "../Input/PlayerPositionChangedEvent.h"
#include "../Ecs/ComponentCreatedEvent.h"
#include "../Physics/MovementSystem.h"
#include "../Physics/CollisionSystem.h"
#include "../Physics/CollisionEngine.h"
#include "../Physics/InitCollisionEngineEvent.h"

// TODO includes for createMovingCube, remove later
#include "../Geometry/PositionComponent.h"
#include "../Geometry/RotationComponent.h"
#include "../Graphics/Render/RenderableComponent.h"
#include "../Graphics/Render/ModelUtils.h"
#include "../Physics/MovementComponent.h"
#include "../Physics/GravityComponent.h"
#include "../Physics/CollisionComponent.h"
#include "../Physics/AABBCollisionBody.h"
#include "../Geometry/AxisAlignedBoundingBox.h"

namespace Application
{
    // TODO method for tests, to be removed
    void createMovingCube(Ecs::World& world)
    {
        // TODO: method AABB from model 3d
        Geometry::AxisAlignedBoundingBox bbox(Geometry::Vec3Df(50.0, 50.0, 145.0), Geometry::Vec3Df(55.0, 55.0, 150.0));

        const Ecs::Entity& entity = world.createEntity();
        world.addComponent(
            entity,
            new Geometry::PositionComponent(Geometry::Vec3Df(50.0, 50.0, 145.0))
        );
        world.addComponent(
            entity,
            new Geometry::RotationComponent(Geometry::Vec3Df())
        );
        world.addComponent(
            entity,
            new Graphics::Render::RenderableComponent(
                Graphics::Render::createPrettyCubeModel()
            )
        );
        world.addComponent(
            entity,
            new Physics::MovementComponent(Geometry::Vec3Df(1.0, 1.0, 20.0))
        );
        world.addComponent(
            entity,
            new Physics::GravityComponent(1)
        );
        world.addComponent(
            entity,
            new Physics::CollisionComponent(Physics::AABBCollisionBody(bbox))
        );
    }

    void Application::start()
    {
        setupEventThread();
        setupGraphicsThread();
        setupUpdateThread();
        setupGenerationThread();

        eventThread_->start();
        graphicsThread_->start();
        updateThread_->start();
        generationThread_->start();

        createMovingCube(ecsWorld_);

        running_ = true;
        while (running_)
        {
            Threading::sleep(1, 0);
        }

        eventThread_->stop();
        updateThread_->stop();
        graphicsThread_->stop();
        generationThread_->stop();
    }

    void Application::setupEventThread()
    {
        std::vector<Threading::ThreadableInterface*> eventThreadables;
        eventThreadables.push_back(&eventManager_);
        eventThread_ = new Threading::Thread(eventThreadables, 300);
    }

    void Application::setupGraphicsThread()
    {
        Event::ListenerRegister& reg = eventManager_.getListenerRegister();
        Event::EventQueue& queue = eventManager_.getEventQueue();

        reg.put(Graphics::CloseDeviceEvent::TYPE, this);

        Graphics::Device* dev = new Graphics::Device(queue);
        reg.put(Input::InputInitializedEvent::TYPE, dev);

        Graphics::Render::Scene* scene = new Graphics::Render::Scene(queue);
        scene->registerListeners(reg);

        Input::IrrlichtInputReceiver* receiver =
            new Input::IrrlichtInputReceiver(queue);
        reg.put(Input::InitInputEvent::TYPE, receiver);

        std::vector<Threading::ThreadableInterface*> graphicsThreadables;
        graphicsThreadables.push_back(dev);
        graphicsThreadables.push_back(scene);
        graphicsThreadables.push_back(receiver);

        Graphics::Render::RenderSystem* rs =
            new Graphics::Render::RenderSystem(ecsWorld_, queue);
        reg.put(Ecs::ComponentCreatedEvent::TYPE, rs);

        graphicsThread_ = new Threading::Thread(graphicsThreadables, 60);
    }

    void Application::setupUpdateThread()
    {
        Event::ListenerRegister& reg = eventManager_.getListenerRegister();

        Physics::MovementSystem* movementSystem =
            new Physics::MovementSystem(ecsWorld_, eventManager_.getEventQueue());

        Physics::CollisionEngine* collisionEngine =
            new Physics::CollisionEngine();

        Physics::CollisionSystem* collisionSystem =
            new Physics::CollisionSystem(ecsWorld_, eventManager_.getEventQueue(), movementSystem->getTimer(), *collisionEngine);

        reg.put(Physics::InitCollisionEngineEvent::TYPE, collisionEngine);
        reg.put(Ecs::ComponentCreatedEvent::TYPE, collisionSystem);

        std::vector<Threading::ThreadableInterface*> threadables;
        threadables.push_back(movementSystem);
        threadables.push_back(collisionEngine);
        threadables.push_back(collisionSystem);

        updateThread_ = new Threading::Thread(threadables, 80);
    }

    void Application::setupGenerationThread()
    {
        World::Generation::ChunkGenerator generator(world_, ecsWorld_, 42);

        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                generator.generateChunk(i, j);
            }
        }

        // TODO Change world seed at each run :-)
        World::Generation::ChunkGenerationSystem* generation =
            new World::Generation::ChunkGenerationSystem(
                ecsWorld_,
                generator
            );

        generation->registerListeners(eventManager_.getListenerRegister());

        std::vector<Threading::ThreadableInterface*> threadables;
        threadables.push_back(generation);

        generationThread_ = new Threading::Thread(threadables, 1);
    }

    void Application::call(const Event::Event& event)
    {
        running_ = false;
    }
}
