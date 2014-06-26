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
#include "HandAction.h"
#include "StatisticsComponent.h"
#include "CharacterComponent.h"
#include "HarmComponent.h"

using Geometry::Vec3Df;
using Geometry::PositionComponent;
using Geometry::RotationComponent;
using Geometry::AxisAlignedBoundingBox;

namespace Character
{
    Ecs::Entity createCharacter(
        Threading::ConcurrentWriter<Ecs::World>& world,
        const Vec3Df& position,
        const Vec3Df& rotation,
        const Statistics& statistics,
        const Ecs::Entity& group,
        Event::EventQueue& queue
    ) {
        // TODO: method AABB from model 3d
        AxisAlignedBoundingBox bbox(
            Vec3Df(-0.5, -0.5, 0.0),
            Vec3Df(0.5, 0.5, 2.0)
        );

        Graphics::Render::AnimationMap animMap;
        animMap[Graphics::Render::Idle] =
            Graphics::Render::AnimationParameters(5.0f, true, Graphics::Render::NoAnimation);
        animMap[Graphics::Render::Walk] =
            Graphics::Render::AnimationParameters(5.0f, true, Graphics::Render::NoAnimation);
        animMap[Graphics::Render::Attack] =
            Graphics::Render::AnimationParameters(5.0f, true, Graphics::Render::NoAnimation);

        std::map<Character::Action::Type, Graphics::Render::AnimationType> animByAction;
        animByAction[Character::MoveAction::Type] = Graphics::Render::Walk;
        animByAction[Character::StopAction::Type] = Graphics::Render::Idle;
        animByAction[Character::StartHandAction::Type] = Graphics::Render::Attack;
        animByAction[Character::StopHandAction::Type] = Graphics::Render::Idle;

        const Ecs::Entity& entity = world->createEntity();
        world->addComponent(
            entity,
            new PositionComponent(position)
        );
        world->addComponent(
            entity,
            new RotationComponent(rotation)
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
            new Physics::MovementComponent(Vec3Df(0.0, 0.0, 0.0))
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

        {
            Threading::ConcurrentWriter<GroupComponent> groupComponent =
                Threading::getConcurrentWriter<Ecs::Component, GroupComponent>(
                    world->getEntityComponent(group, GroupComponent::Type)
                );

            groupComponent->setCurrentHealth(
                groupComponent->getCurrentHealth() +
                statistics.getHealth().getBaseValue()
            );
        }

        associateToGroup(world, entity, group, queue);

        return entity;
    }

    Ecs::Entity createPlayer(
        Threading::ConcurrentWriter<Ecs::World>& world,
        const Vec3Df& position,
        const Vec3Df& rotation,
        const Statistics& statistics,
        const Ecs::Entity& group,
        Event::EventQueue& queue
    ) {
        Ecs::Entity entity = createCharacter(
            world,
            position,
            rotation,
            statistics,
            group,
            queue
        );


        world->addComponent(
            entity,
            new Input::PlayerComponent()
        );

        return entity;
    }

    Ecs::Entity createAttackArea(
        Threading::ConcurrentWriter<Ecs::World>& world,
        const Ecs::Entity& character
    ) {
        Ecs::Entity area = world->createEntity();
        Vec3Df basePosition;
        Vec3Df rotation;
        unsigned int damages = 0;

        {
            Ecs::ComponentGroup::ComponentTypeCollection types;
            types.insert(StatisticsComponent::Type);
            types.insert(CharacterComponent::Type);
            types.insert(PositionComponent::Type);
            types.insert(RotationComponent::Type);
            Ecs::ComponentGroup prototype(types);

            Ecs::ComponentGroup group = world->getEntityComponents(
                character,
                prototype
            );

            Threading::ConcurrentWriter<CharacterComponent> characterComponent =
                Threading::getConcurrentWriter<Ecs::Component, CharacterComponent>(
                    group.getComponent(CharacterComponent::Type)
                );

            Threading::ConcurrentReader<StatisticsComponent> statComponent =
                Threading::getConcurrentReader<Ecs::Component, StatisticsComponent>(
                    group.getComponent(StatisticsComponent::Type)
                );

            Threading::ConcurrentReader<PositionComponent> posComponent =
                Threading::getConcurrentReader<Ecs::Component, PositionComponent>(
                    group.getComponent(PositionComponent::Type)
                );

            Threading::ConcurrentReader<RotationComponent> rotComponent =
                Threading::getConcurrentReader<Ecs::Component, RotationComponent>(
                    group.getComponent(RotationComponent::Type)
                );

            damages = statComponent->getStatistics().getAttack().getCurrentValue();
            characterComponent->setAttackArea(area);
            basePosition = posComponent->getPosition();
            rotation = rotComponent->getRotation();
        }

        Geometry::Vec2Df offset = Geometry::Vec2Df::fromPolar(
            rotation.getZ(),
            1.2
        ) - Geometry::Vec2Df(0.5, 0.5);

        Geometry::AxisAlignedBoundingBox bbox(
            Geometry::Vec3Df(0.0, 0.0, 0.0),
            Geometry::Vec3Df(1.0, 1.0, 1.0)
        );

        world->addComponent(area, new PositionComponent(
            basePosition + Vec3Df(offset.getX(), offset.getY(), 0)
        ));
        world->addComponent(area, new RotationComponent(
            Vec3Df(0, 0, 0)
        ));
        world->addComponent(area, new Physics::CollisionComponent(
            new Physics::AABBCollisionBody(bbox)
        ));
        world->addComponent(area, new HarmComponent(
            damages
        ));

        return area;
    }
}
