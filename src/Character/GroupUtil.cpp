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

#include "GroupUtil.h"

#include "CharacterComponent.h"
#include "GroupComponent.h"
#include "StatisticsComponent.h"
#include "GroupMaxHealthChangedEvent.h"
#include "GroupCurrentHealthChangedEvent.h"
#include "../Input/PlayerComponent.h"

namespace Character
{
    void associateToGroup(
        Threading::ConcurrentWriter<Ecs::World>& world,
        const Ecs::Entity& entity,
        const Ecs::Entity& group,
        Event::EventQueue& eventQueue
    ) {
        unsigned int currentHealth = 0;
        {
            Threading::ConcurrentWriter<CharacterComponent> characterComponent =
                Threading::getConcurrentWriter<Ecs::Component, CharacterComponent>(
                    world->getEntityComponent(entity, CharacterComponent::Type)
                );

            Threading::ConcurrentWriter<GroupComponent> groupComponent =
                Threading::getConcurrentWriter<Ecs::Component, GroupComponent>(
                    world->getEntityComponent(group, GroupComponent::Type)
                );

            Ecs::Entity oldGroup = characterComponent->getGroup();

            if (oldGroup != group) {
                Threading::ConcurrentWriter<GroupComponent> oldGroupComponent =
                    Threading::getConcurrentWriter<Ecs::Component, GroupComponent>(
                        world->getEntityComponent(oldGroup, GroupComponent::Type)
                    );

                oldGroupComponent->removeEntity(entity);
            }

            characterComponent->setGroup(group);
            groupComponent->addEntity(entity);
            currentHealth = groupComponent->getCurrentHealth();
        }

        eventQueue << new GroupMaxHealthChangedEvent(
            group,
            computeMaxHealth(world, group)
        );

        eventQueue << new GroupCurrentHealthChangedEvent(
            group,
            currentHealth
        );

    }

    unsigned int computeMaxHealth(
        Threading::ConcurrentWriter<Ecs::World>& world,
        const Ecs::Entity& group
    ) {
        unsigned int health = 0;

        Threading::ConcurrentReader<GroupComponent> groupComponent =
            Threading::getConcurrentReader<Ecs::Component, GroupComponent>(
                world->getEntityComponent(group, GroupComponent::Type)
            );

        const GroupComponent::EntityCollection& entities =
            groupComponent->getEntities();

        GroupComponent::EntityCollection::const_iterator entity;
        for (entity = entities.begin(); entity != entities.end(); ++entity)
        {
            Threading::ConcurrentReader<StatisticsComponent> statisticsComponent =
                Threading::getConcurrentReader<Ecs::Component, StatisticsComponent>(
                    world->getEntityComponent(*entity, StatisticsComponent::Type)
                );

            health += statisticsComponent->getStatistics().getHealth().getBaseValue();
        }

        return health;
    }

    void initGroupHealth(
        Threading::ConcurrentWriter<Ecs::World>& world,
        const Ecs::Entity& group
    ) {
        unsigned int maxHealth = computeMaxHealth(world, group);

        Threading::ConcurrentWriter<GroupComponent> groupComponent =
            Threading::getConcurrentWriter<Ecs::Component, GroupComponent>(
                world->getEntityComponent(group, GroupComponent::Type)
            );

        groupComponent->setCurrentHealth(maxHealth);
    }

    bool isPlayerGroup(
        Threading::ConcurrentWriter<Ecs::World>& world,
        const Ecs::Entity& group
    ) {
        Threading::ConcurrentReader<GroupComponent> groupComponent =
            Threading::getConcurrentReader<Ecs::Component, GroupComponent>(
                world->getEntityComponent(group, GroupComponent::Type)
            );

        const GroupComponent::EntityCollection& entities =
            groupComponent->getEntities();

        GroupComponent::EntityCollection::const_iterator entity;
        for (entity = entities.begin(); entity != entities.end(); ++entity)
        {
            if (world->hasComponent(*entity, Input::PlayerComponent::Type))
            {
                return true;
            }
        }

        return false;
    }
}
