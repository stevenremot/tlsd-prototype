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

namespace Character
{
    void associateToGroup(
        Threading::ConcurrentWriter<Ecs::World>& world,
        const Ecs::Entity& entity,
        const Ecs::Entity& group
    ) {
        Threading::ConcurrentWriter<CharacterComponent> characterComponent =
            Threading::getConcurrentWriter<Ecs::Component, CharacterComponent>(
                world->getEntityComponent(entity, CharacterComponent::Type)
            );

        Threading::ConcurrentWriter<GroupComponent> groupComponent =
            Threading::getConcurrentWriter<Ecs::Component, GroupComponent>(
                world->getEntityComponent(group, GroupComponent::Type)
            );

        if (characterComponent->hasGroup())
        {
            Ecs::Entity oldGroup = characterComponent->getGroup();

            if (oldGroup != group) {
                Threading::ConcurrentWriter<GroupComponent> oldGroupComponent =
                    Threading::getConcurrentWriter<Ecs::Component, GroupComponent>(
                        world->getEntityComponent(oldGroup, GroupComponent::Type)
                    );

                oldGroupComponent->removeEntity(entity);
            }
        }

        characterComponent->setGroup(group);
        groupComponent->addEntity(entity);
    }
}
