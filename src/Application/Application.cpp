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

#include <iostream> // TODO remove

// TODO includes for group, remove later
#include "../Character/GroupComponent.h"
#include "../Character/EntityCreator.h"
#include "../Character/Statistics.h"

// TODO incudes forcube, remove later
#include "../Geometry/PositionComponent.h"
#include "../Geometry/RotationComponent.h"
#include "../Geometry/AxisAlignedBoundingBox.h"
#include "../Physics/CollisionComponent.h"
#include "../Physics/AABBCollisionBody.h"
#include "../Character/HarmComponent.h"
#include "../Graphics/Render/RenderableComponent.h"
#include "../Graphics/Render/ModelUtils.h"

namespace Application
{
    /**
     * Dangerous cube for testing
     * TODO remove
     */
    Ecs::Entity createDangerousCube(
        Threading::ConcurrentWriter<Ecs::World>& world,
        const Geometry::Vec3Df& position,
        unsigned int damages
    ) {
        Geometry::AxisAlignedBoundingBox bbox(
            position + Geometry::Vec3Df(0.0, 0.0, 0.0),
            position + Geometry::Vec3Df(1.0, 1.0, 1.0));

        Ecs::Entity entity = world->createEntity();

        world->addComponent(entity, new Geometry::PositionComponent(position));
        world->addComponent(entity, new Geometry::RotationComponent(
            Geometry::Vec3Df(0, 0, 0)
        ));
        world->addComponent(entity, new Physics::CollisionComponent(
            new Physics::AABBCollisionBody(bbox)
        ));
        world->addComponent(entity, new Character::HarmComponent(damages));
        world->addComponent(entity, new Graphics::Render::RenderableComponent(
            Graphics::Render::createPrettyCubeModel()
        ));

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
                Character::Statistics(100, 20, 20, 5),
                group
            );
            Character::createCharacter(
                world,
                Geometry::Vec3Df(160, 160, 150),
                Geometry::Vec3Df(0, 0, 0),
                Character::Statistics(70, 20, 20, 5),
                group
            );

            createDangerousCube(world, Geometry::Vec3Df(200, 200, 0), 20);

            std::cout << groupComponent->getCurrentHealth() << std::endl;
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
