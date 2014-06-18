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
#include "../Graphics/Render/AnimationSystem.h"
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
#include "../Character/CharacterSystem.h"
#include "../Character/CharacterComponent.h"
#include "../Input/PlayerSystem.h"
#include "../Input/PlayerComponent.h"

// TODO: includes for createPlayer, remove later
#include "../Character/MoveAction.h"
#include "../Character/StopAction.h"

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
            new Physics::CollisionComponent(new Physics::AABBCollisionBody(bbox))
        );
    }

    void createPlayer(Ecs::World& world, const Geometry::Vec3Df& position, const Geometry::Vec3Df& rotation)
    {
        // TODO: method AABB from model 3d
        Geometry::AxisAlignedBoundingBox bbox(Geometry::Vec3Df(150.0, 150.0, 0.0), Geometry::Vec3Df(150.5, 150.5, 1.0));

        Graphics::Render::AnimationMap animMap;
        animMap[Graphics::Render::Idle] =
            Graphics::Render::AnimationParameters(5.0f, true, Graphics::Render::NoAnimation);
        animMap[Graphics::Render::Walk] =
            Graphics::Render::AnimationParameters(5.0f, true, Graphics::Render::NoAnimation);

        std::map<Character::Action::Type, Graphics::Render::AnimationType> animByAction;
        animByAction[Character::MoveAction::Type] = Graphics::Render::Walk;
        animByAction[Character::StopAction::Type] = Graphics::Render::Idle;

        const Ecs::Entity& entity = world.createEntity();
        world.addComponent(
            entity,
            new Geometry::PositionComponent(position)
        );
        world.addComponent(
            entity,
            new Geometry::RotationComponent(rotation)
        );
        world.addComponent(
            entity,
            new Graphics::Render::RenderableComponent(
                "ninja.b3d", ""
            )
        );
        world.addComponent(
            entity,
            new Graphics::Render::AnimationComponent(animMap, animByAction)
        );
        world.addComponent(
            entity,
            new Physics::MovementComponent(Geometry::Vec3Df(0.0, 0.0, 0.0))
        );
        world.addComponent(
            entity,
            new Physics::GravityComponent(1)
        );
        world.addComponent(
            entity,
            new Physics::CollisionComponent(new Physics::AABBCollisionBody(bbox))
        );
        world.addComponent(
            entity,
            new Character::CharacterComponent(5.0)
        );
        world.addComponent(
            entity,
            new Input::PlayerComponent()
        );
    }

    void Application::start()
    {
        setupEventThread();
        setupGraphicsThread();
        setupUpdateThread();
        setupGenerationThread();
        setupCharacterThread();
        setupAnimationThread();

        eventThread_->start();
        graphicsThread_->start();
        updateThread_->start();
        generationThread_->start();
        characterThread_->start();
        animationThread_->start();

        //createMovingCube(ecsWorld_);
        createPlayer(ecsWorld_, Geometry::Vec3Df(300,300,0), Geometry::Vec3Df(0,0,90));

        running_ = true;
        while (running_)
        {
            Threading::sleep(1, 0);
        }

        eventThread_->stop();
        updateThread_->stop();
        graphicsThread_->stop();
        generationThread_->stop();
        characterThread_->stop();
        animationThread_->stop();
    }

    void Application::setupEventThread()
    {
        std::vector<Threading::ThreadableInterface*> eventThreadables;
        eventThreadables.push_back(&eventManager_);
        eventThread_ = new Threading::Thread(eventThreadables, 500);
    }

    void Application::setupGraphicsThread()
    {
        Event::ListenerRegister& reg = eventManager_.getListenerRegister();
        Event::EventQueue& queue = eventManager_.getEventQueue();

        reg.put(Graphics::CloseDeviceEvent::Type, this);

        Graphics::Device* dev = new Graphics::Device(queue);
        reg.put(Input::InputInitializedEvent::Type, dev);

        Graphics::Render::Scene* scene = new Graphics::Render::Scene(queue);
        scene->registerListeners(reg);

        Input::IrrlichtInputReceiver* receiver =
            new Input::IrrlichtInputReceiver(queue);
        reg.put(Input::InitInputEvent::Type, receiver);

        Input::PlayerSystem* playerSystem =
            new Input::PlayerSystem(ecsWorld_, eventManager_.getEventQueue());
        playerSystem->registerListeners(reg);

        std::vector<Threading::ThreadableInterface*> graphicsThreadables;
        graphicsThreadables.push_back(dev);
        graphicsThreadables.push_back(scene);
        graphicsThreadables.push_back(receiver);
        graphicsThreadables.push_back(playerSystem);

        Graphics::Render::RenderSystem* rs =
            new Graphics::Render::RenderSystem(ecsWorld_, queue);
        reg.put(Ecs::ComponentCreatedEvent::Type, rs);

        graphicsThread_ = new Threading::Thread(graphicsThreadables, 60);
    }

    void Application::setupUpdateThread()
    {
        Event::ListenerRegister& reg = eventManager_.getListenerRegister();

        Physics::MovementSystem* movementSystem =
            new Physics::MovementSystem(ecsWorld_, eventManager_.getEventQueue());

        Physics::CollisionSystem* collisionSystem =
            new Physics::CollisionSystem(ecsWorld_, eventManager_.getEventQueue(), movementSystem->getTimer());

        std::vector<Threading::ThreadableInterface*> threadables;
        threadables.push_back(movementSystem);
        threadables.push_back(collisionSystem);

        updateThread_ = new Threading::Thread(threadables, 100);
    }

    void Application::setupCharacterThread()
    {
        Event::ListenerRegister& reg = eventManager_.getListenerRegister();

        Character::CharacterSystem* characterSystem =
            new Character::CharacterSystem(ecsWorld_, eventManager_.getEventQueue());
        characterSystem->registerListeners(reg);

        std::vector<Threading::ThreadableInterface*> threadables;
        threadables.push_back(characterSystem);

        characterThread_ = new Threading::Thread(threadables, 60);

    }

    void Application::setupAnimationThread()
    {
        Graphics::Render::AnimationSystem* as =
            new Graphics::Render::AnimationSystem(ecsWorld_, eventManager_.getEventQueue());
        as->registerListeners(eventManager_.getListenerRegister());

        std::vector<Threading::ThreadableInterface*> animThreadables;
        animThreadables.push_back(as);

        animationThread_ = new Threading::Thread(animThreadables, 60);
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
