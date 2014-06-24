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

// TODO: includes for createPlayer, remove later
#include "../Character/MoveAction.h"
#include "../Character/StopAction.h"
#include "../Character/StatisticsComponent.h"
#include "../Character/CharacterComponent.h"
#include "../Input/PlayerComponent.h"

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

// TODO includes for group, remove later
#include "../Character/GroupComponent.h"
#include "../Character/GroupUtil.h"

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

    Ecs::Entity createPlayer(Ecs::World& world, const Geometry::Vec3Df& position, const Geometry::Vec3Df& rotation)
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
            new Character::StatisticsComponent(
                Character::Statistics(100, 20, 20, 20)
            )
        );
        world.addComponent(
            entity,
            new Character::CharacterComponent(5.0)
        );
        world.addComponent(
            entity,
            new Input::PlayerComponent()
        );

        return entity;
    }

    Ecs::Entity createBuddy(Ecs::World& world, const Geometry::Vec3Df& position, const Geometry::Vec3Df& rotation)
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
            new Character::StatisticsComponent(
                Character::Statistics(100, 20, 20, 20)
            )
        );
        world.addComponent(
            entity,
            new Character::CharacterComponent(5.0)
        );

        return entity;
    }

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
        application.startLoop();
    }

    Application::Application():
        eventBoot_(applicationEventBootCallback, *this),
        ecsWorld_(new Ecs::World(eventBoot_.getEventManager().getEventQueue())),
        world_(),
        graphicsBoot_(applicationGraphicsBootCallback, *this),
        updateBoot_(applicationUpdateBootCallback, *this),
        generationBoot_(applicationGenerationBootCallback, *this),
        characterBoot_(applicationCharacterBootCallback, *this),
        animationBoot_(applicationAnimationBootCallback, *this),
        running_(false)
    {}

    void Application::start()
    {
        eventBoot_.start();
    }

    void Application::startLoop()
    {
        //createMovingCube(ecsWorld_);
        // TODO set z at 0, not 150
        {
            Threading::ConcurrentWriter<Ecs::World> world = ecsWorld_.getWriter();
            Ecs::Entity player = createPlayer(
                *world,
                Geometry::Vec3Df(150,150,150),
                Geometry::Vec3Df(0,0,0)
            );
            Ecs::Entity buddy = createBuddy(
                *world,
                Geometry::Vec3Df(160, 160, 150),
                Geometry::Vec3Df(0, 0, 0)
            );

            Ecs::Entity group = world->createEntity();
            world->addComponent(group, new Character::GroupComponent());

            Character::associateToGroup(world, player, group);
            Character::associateToGroup(world, buddy, group);
        }

        running_ = true;
        while (running_)
        {
            Threading::sleep(1, 0);
        }

    }

    void Application::call(const Event::Event& event)
    {
        running_ = false;
    }
}
