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
#include "PlayerComponent.h"
#include "../Character/MoveAction.h"
#include "../Character/StopAction.h"
#include "../Character/LookAtAction.h"
#include "../Character/HandAction.h"
#include "../Character/ActionPerformedEvent.h"
#include "../Geometry/RotationComponent.h"
#include "../Geometry/PositionComponent.h"
#include "../Graphics/Render/RenderEvents.h"

using Graphics::Render::CameraRenderedEvent;

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
        else if (event.getType() == CameraEvent::Type)
        {
            eventQueue_ << new CameraEvent(
                            dynamic_cast<const CameraEvent&>(event)
                        );
        }
        else if (event.getType() == CameraRenderedEvent::Type)
        {
            eventQueue_ << new CameraRenderedEvent(
                dynamic_cast<const CameraRenderedEvent&>(event)
            );
        }
        else if (event.getType() == StopActionEvent::Type)
        {
            eventQueue_ << new StopActionEvent(
                            dynamic_cast<const StopActionEvent&>(event)
                        );
        }
        else if (event.getType() == ActionEvent::Type)
        {
            eventQueue_ << new ActionEvent(
                            dynamic_cast<const ActionEvent&>(event)
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
                Ecs::ComponentGroup::ComponentTypeCollection types;
                types.insert(PlayerComponent::Type);
                types.insert(Geometry::RotationComponent::Type);
                types.insert(Geometry::PositionComponent::Type);

                Ecs::ComponentGroup prototype(types);
                Ecs::World::ComponentGroupCollection groups =
                    getWorld()->getComponents(prototype);

                Ecs::World::ComponentGroupCollection::iterator group;
                for (group = groups.begin(); group != groups.end(); ++group)
                {
                    const Ecs::Entity& entity = group->getEntity();


                    Threading::ConcurrentWriter<PlayerComponent> playerComponent =
                        Threading::getConcurrentWriter<Ecs::Component, PlayerComponent>(
                            group->getComponent(PlayerComponent::Type)
                        );

                    Character::Action* action = NULL;
                    if (event->getType() == MoveEvent::Type)
                    {
                        const MoveEvent& evt =
                            dynamic_cast<const MoveEvent&>(*event);

                        Threading::ConcurrentReader<Geometry::RotationComponent> component =
                            Threading::getConcurrentReader<Ecs::Component, Geometry::RotationComponent>(group->getComponent(Geometry::RotationComponent::Type));

                        Threading::ConcurrentReader<Geometry::PositionComponent> positionComponent =
                            Threading::getConcurrentReader<Ecs::Component, Geometry::PositionComponent>(group->getComponent(Geometry::PositionComponent::Type));

                        const Geometry::Vec3Df& rotation = component->getRotation();
                        const float camOrientation = rotation.getZ();

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
                    else if (
                        event->getType() == CameraEvent::Type &&
                        playerComponent->isCameraSet()
                    )
                    {
                        const CameraEvent& evt = dynamic_cast<const CameraEvent&>(*event);
                        const Geometry::Vec2Df& cursorPos = evt.getCursorPosition();
                        Graphics::Render::CameraSceneNode& camera = playerComponent->getCamera();

                        camera.updateTarget(cursorPos);

                        const float newOrientation = camera.getHorizontalRotation();

                        action = new Character::LookAtAction(newOrientation);
                    }
                    else if (event->getType() == CameraRenderedEvent::Type)
                    {
                        const CameraRenderedEvent& evt =
                            dynamic_cast<const CameraRenderedEvent&>(*event);

                        playerComponent->setCamera(evt.getCamera());
                    }
                    else if (event->getType() == ActionEvent::Type)
                    {
                        const ActionEvent& evt =
                            dynamic_cast<const ActionEvent&>(*event);

                        Character::Hand hand;
                        switch (evt.getActionType())
                        {
                        case ActionEvent::LeftActionType:
                            hand = Character::LeftHand;
                            break;
                        default:
                            hand = Character::RightHand;
                            break;
                        }

                        action = new Character::StartHandAction(hand);
                    }
                    else if (event->getType() == StopActionEvent::Type)
                    {
                        const StopActionEvent& evt =
                            dynamic_cast<const StopActionEvent&>(*event);

                        Character::Hand hand;
                        switch (evt.getActionType())
                        {
                        case ActionEvent::LeftActionType:
                            hand = Character::LeftHand;
                            break;
                        default:
                            hand = Character::RightHand;
                            break;
                        }

                        action = new Character::StopHandAction(hand);
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
        listener.put(CameraEvent::Type, this);
        listener.put(CameraRenderedEvent::Type, this);
        listener.put(ActionEvent::Type, this);
        listener.put(StopActionEvent::Type, this);
    }

    void PlayerSystem::unregisterListeners(Event::ListenerRegister& listener)
    {
        listener.remove(this);
    }
}
