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

#include "PlayerSystem.h"

#include <cmath>

#include "Events.h"
#include "../Character/MoveAction.h"
#include "../Character/StopAction.h"
#include "../Character/ActionPerformedEvent.h"
#include "PlayerComponent.h"
#include "../Geometry/RotationComponent.h"

namespace Input
{
    void PlayerSystem::call(const Event::Event& event)
    {
        if (event.getType() == MoveEvent::Type)
        {
            eventQueue_ << new MoveEvent(
                            dynamic_cast<const MoveEvent&>(event)
                        );
        }
    }

    void PlayerSystem::run()
    {
        while (!eventHead_.isEmpty())
        {
            Event::Event* event = NULL;
            eventHead_ >> event;

            if (event != NULL)
            {
                Ecs::World& world = getWorld();

                Ecs::ComponentGroup::ComponentTypeCollection types;
                types.insert(PlayerComponent::Type);
                types.insert(Geometry::RotationComponent::Type);

                Ecs::ComponentGroup prototype(types);
                Ecs::World::ComponentGroupCollection groups =
                    world.getComponents(prototype);

                Ecs::World::ComponentGroupCollection::iterator group;
                for (group = groups.begin(); group != groups.end(); ++group)
                {
                    const Ecs::Entity& entity = group->getEntity();
                    const Geometry::RotationComponent& component =
                        dynamic_cast<Geometry::RotationComponent&>(group->getComponent(Geometry::RotationComponent::Type));
                    const Geometry::Vec3Df& rotation = component.getRotation();
                    const float camOrientation = rotation.getZ() / 180.0 * M_PI;

                    Character::Action* action = NULL;
                    if (event->getType() == MoveEvent::Type)
                    {
                        const MoveEvent& evt =
                            dynamic_cast<const MoveEvent&>(*event);

                        if (evt.getDirection() == Geometry::Vec2Df(0,0))
                            action = new Character::StopAction();
                        else
                        {
                            const float orientation =
                                evt.getDirection().getOrientation();

                            const Geometry::Vec2Df v = Geometry::Vec2Df::fromPolar(
                                                           orientation + camOrientation,
                                                           1.0
                                                       );

                            action = new Character::MoveAction(v);
                        }
                    }

                    if (action != NULL)
                    {
                        outsideQueue_ << new Character::ActionPerformedEvent(
                                          entity,
                                          action
                                      );
                    }
                }
                delete event;
            }
        }
    }

    void PlayerSystem::registerListeners(Event::ListenerRegister& listener)
    {
        listener.put(MoveEvent::Type, this);
    }
}
