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

#include "StatSystem.h"

#include <algorithm>
#include <iostream>

#include "HurtEvent.h"
#include "HarmComponent.h"
#include "CharacterComponent.h"
#include "DieAction.h"
#include "ActionPerformedEvent.h"
#include "GroupComponent.h"

namespace Character
{
    void StatSystem::call(const Event::Event& event)
    {
        if (event.getType() == HurtEvent::Type)
        {
            eventQueue_ << new HurtEvent(
                dynamic_cast<const HurtEvent&>(event)
            );
        }
    }

    void StatSystem::run()
    {
        while (!eventHead_.isEmpty())
        {
            Event::Event* event = NULL;
            eventHead_ >> event;

            if (event != NULL)
            {
                if (event->getType() == HurtEvent::Type)
                {
                    Threading::ConcurrentWriter<Ecs::World> world = getWorld();

                    const HurtEvent& evt = dynamic_cast<const HurtEvent&>(*event);
                    const Ecs::Entity& attacker = evt.getAttacker();
                    const Ecs::Entity& receiver = evt.getReceiver();
                    Threading::ConcurrentRessource<Ecs::Component> harmComponentRessource =
                        world->getEntityComponent(attacker, HarmComponent::Type);

                    Threading::ConcurrentRessource<Ecs::Component> charComponentRessource =
                        world->getEntityComponent(receiver, CharacterComponent::Type);

                    Threading::ConcurrentRessource<Ecs::Component> statComponentRessource =
                        world->getEntityComponent(receiver, StatisticsComponent::Type);

                    const Ecs::Entity& group =
                        Threading::getConcurrentReader<Ecs::Component, CharacterComponent>(
                            charComponentRessource
                        )->getGroup();

                    Threading::ConcurrentWriter<GroupComponent> groupComponent =
                        Threading::getConcurrentWriter<Ecs::Component, GroupComponent>(
                            world->getEntityComponent(group, GroupComponent::Type)
                        );

                    Threading::ConcurrentReader<HarmComponent> harmComponent =
                        Threading::getConcurrentReader<Ecs::Component, HarmComponent>(
                            harmComponentRessource
                        );
                    Threading::ConcurrentWriter<StatisticsComponent> statComponent =
                        Threading::getConcurrentWriter<Ecs::Component, StatisticsComponent>(
                            statComponentRessource
                        );

                    int currentHealth = groupComponent->getCurrentHealth();
                    int damages = std::max<int>(
                        static_cast<float>(harmComponent->getDamages()) -
                        static_cast<float>(statComponent->getStatistics().getDefense().getCurrentValue()),
                        1
                    );

                    if (damages > currentHealth)
                    {
                        groupComponent->setCurrentHealth(0);
                        outsideQueue_ << new ActionPerformedEvent(
                            group,
                            new DieAction()
                        );
                    }
                    else
                    {
                        groupComponent->setCurrentHealth(currentHealth - damages);
                    }

                    // TODO remove
                    std::cout << "Health : " << groupComponent->getCurrentHealth() << std::endl;
                }

                delete event;
            }
        }
    }

    void StatSystem::registerListeners(Event::ListenerRegister& reg)
    {
        reg.put(HurtEvent::Type, this);
    }

    void StatSystem::unregisterListeners(Event::ListenerRegister& reg)
    {
        reg.remove(this);
    }
}
