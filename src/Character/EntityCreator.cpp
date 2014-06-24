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

#include "EntityCreator.h"

#include "../Geometry/PositionComponent.h"
#include "../Geometry/RotationComponent.h"
#include "../Geometry/AxisAlignedBoundingBox.h"
#include "../Graphics/Render/RenderableComponent.h"
#include "../Graphics/Render/ModelUtils.h"
#include "../Physics/MovementComponent.h"
#include "../Physics/GravityComponent.h"
#include "../Physics/CollisionComponent.h"
#include "../Physics/AABBCollisionBody.h"
#include "../Input/PlayerComponent.h"
#include "GroupComponent.h"
#include "GroupUtil.h"
#include "MoveAction.h"
#include "StopAction.h"
#include "StatisticsComponent.h"
#include "CharacterComponent.h"

namespace Character
{
    Ecs::Entity createCharacter(
        Threading::ConcurrentWriter<Ecs::World>& world,
        const Geometry::Vec3Df& position,
        const Geometry::Vec3Df& rotation,
        const Statistics& statistics,
        const Ecs::Entity& group
    ) {
        // TODO: method AABB from model 3d
        Geometry::AxisAlignedBoundingBox bbox(
            Geometry::Vec3Df(-0.5, -0.5, 0.0),
            Geometry::Vec3Df(0.5, 0.5, 2.0)
        );

        Graphics::Render::AnimationMap animMap;
        animMap[Graphics::Render::Idle] =
            Graphics::Render::AnimationParameters(5.0f, true, Graphics::Render::NoAnimation);
        animMap[Graphics::Render::Walk] =
            Graphics::Render::AnimationParameters(5.0f, true, Graphics::Render::NoAnimation);

        std::map<Character::Action::Type, Graphics::Render::AnimationType> animByAction;
        animByAction[Character::MoveAction::Type] = Graphics::Render::Walk;
        animByAction[Character::StopAction::Type] = Graphics::Render::Idle;

        const Ecs::Entity& entity = world->createEntity();
        world->addComponent(
            entity,
            new Geometry::PositionComponent(position)
        );
        world->addComponent(
            entity,
            new Geometry::RotationComponent(rotation)
        );
        world->addComponent(
            entity,
            new Graphics::Render::RenderableComponent(
                "ninja.b3d", ""
            )
        );
        world->addComponent(
            entity,
            new Graphics::Render::AnimationComponent(animMap, animByAction)
        );
        world->addComponent(
            entity,
            new Physics::MovementComponent(Geometry::Vec3Df(0.0, 0.0, 0.0))
        );
        world->addComponent(
            entity,
            new Physics::GravityComponent(1)
        );
        world->addComponent(
            entity,
            new Physics::CollisionComponent(new Physics::AABBCollisionBody(bbox))
        );
        world->addComponent(
            entity,
            new Character::StatisticsComponent(
                statistics
            )
        );
        world->addComponent(
            entity,
            new Character::CharacterComponent(
                statistics.getSpeed().getBaseValue(),
                group
            )
        );

        associateToGroup(world, entity, group);

        Threading::ConcurrentWriter<GroupComponent> groupComponent =
            Threading::getConcurrentWriter<Ecs::Component, GroupComponent>(
                world->getEntityComponent(group, GroupComponent::Type)
            );

        groupComponent->setCurrentHealth(
            groupComponent->getCurrentHealth() +
            statistics.getHealth().getBaseValue()
        );

        return entity;
    }

    Ecs::Entity createPlayer(
        Threading::ConcurrentWriter<Ecs::World>& world,
        const Geometry::Vec3Df& position,
        const Geometry::Vec3Df& rotation,
        const Statistics& statistics,
        const Ecs::Entity& group
    ) {
        Ecs::Entity entity = createCharacter(
            world,
            position,
            rotation,
            statistics,
            group
        );


        world->addComponent(
            entity,
            new Input::PlayerComponent()
        );

        return entity;
    }

}
