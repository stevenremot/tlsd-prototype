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

#include "CharacterSystem.h"

#include "MoveAction.h"
#include "StopAction.h"
#include "LookAtAction.h"
#include "DieAction.h"
#include "ActionPerformedEvent.h"
#include "CharacterComponent.h"
#include "../Input/PlayerComponent.h"
#include "../Physics/MovementComponent.h"
#include "../Physics/EntityRotationChangedEvent.h"
#include "../Graphics/Render/AnimateActionEvent.h"

// TODO remove
#include <iostream>

using Geometry::Vec2Df;
using Geometry::Vec3Df;

namespace Character
{
    void CharacterSystem::call(const Event::Event& event)
    {
        if (event.getType() == ActionPerformedEvent::Type)
        {
            eventQueue_ << new ActionPerformedEvent(dynamic_cast<const ActionPerformedEvent&>(event));
        }
    }

    void CharacterSystem::run()
    {
        while (!eventHead_.isEmpty())
        {
            Event::Event* event = NULL;
            eventHead_ >> event;

            if (event != NULL)
            {
                const ActionPerformedEvent& actionEvent =
                    dynamic_cast<const ActionPerformedEvent&>(*event);

                const Ecs::Entity& entity = actionEvent.getEntity();
                const Character::Action& action = actionEvent.getAction();

                Ecs::ComponentGroup::ComponentTypeCollection types;
                types.insert(CharacterComponent::Type);
                types.insert(Geometry::RotationComponent::Type);
                types.insert(Physics::MovementComponent::Type);
                Ecs::ComponentGroup prototype(types);
                Ecs::ComponentGroup group =
                    getWorld()->getEntityComponents(entity, prototype);

                bool hasPlayer = getWorld()->hasComponent(entity, Input::PlayerComponent::Type);

                bool removeEntity = false;

                {
                    Threading::ConcurrentReader<CharacterComponent> charComponent =
                        Threading::getConcurrentReader<Ecs::Component, CharacterComponent>(
                            group.getComponent(CharacterComponent::Type)
                        );

                    Threading::ConcurrentWriter<Geometry::RotationComponent> rotComponent =
                        Threading::getConcurrentWriter<Ecs::Component, Geometry::RotationComponent>(
                            group.getComponent(
                                Geometry::RotationComponent::Type
                            )
                        );

                    Threading::ConcurrentWriter<Physics::MovementComponent> movementComponent =
                        Threading::getConcurrentWriter<Ecs::Component, Physics::MovementComponent>(
                            group.getComponent(Physics::MovementComponent::Type)
                        );

                    if (action.getType() == MoveAction::Type)
                    {
                        Vec2Df direction2D = dynamic_cast<const MoveAction&>(action).getDirection();
                        Vec3Df velocity =
                            Vec3Df(direction2D.getX(), direction2D.getY(), 0) * charComponent->getWalkingSpeed();

                        movementComponent->setVelocity(velocity);

                        outsideQueue_ << new Graphics::Render::AnimateActionEvent(entity, MoveAction::Type);
                    }
                    else if (action.getType() == StopAction::Type)
                    {
                        movementComponent->setVelocity(Vec3Df(0,0,0));

                        outsideQueue_ << new Graphics::Render::AnimateActionEvent(entity, StopAction::Type);
                    }
                    else if (action.getType() == LookAtAction::Type)
                    {
                        const LookAtAction& lookAction =
                            dynamic_cast<const LookAtAction&>(action);

                        const float orientation = lookAction.getOrientation();
                        const Vec3Df currentOrientation = rotComponent->getRotation();
                        rotComponent->setRotation(
                            Vec3Df(
                                currentOrientation.getX(),
                                currentOrientation.getY(),
                                orientation
                            )
                        );

                        // update movement component orientation
                        Vec2Df currentDirection(movementComponent->getVelocity().getX(),
                                                movementComponent->getVelocity().getY()
                        );
                        float currentAngle = currentDirection.getOrientation();
                        currentAngle += orientation - currentOrientation.getZ();
                        Vec2Df newDirection =
                            Geometry::Vec2Df::fromPolar(currentAngle, currentDirection.getLength());

                        movementComponent->setVelocity(
                            Vec3Df(newDirection.getX(),
                                   newDirection.getY(),
                                   movementComponent->getVelocity().getZ()
                            )
                        );

                        if (!hasPlayer)
                        {
                            outsideQueue_ << new Physics::EntityRotationChangedEvent(
                                entity,
                                rotComponent->getRotation()
                            );
                        }
                    }
                    else if(action.getType() == DieAction::Type)
                    {
                        if (hasPlayer)
                        {
                            std::cout << "You died, noob." << std::endl;
                        }
                        removeEntity = true;
                    }
                }

                if (removeEntity)
                {
                    getWorld()->removeEntity(entity);
                }
            }
        }
    }

    void CharacterSystem::registerListeners(Event::ListenerRegister& reg)
    {
        reg.put(ActionPerformedEvent::Type, this);
    }

    void CharacterSystem::unregisterListeners(Event::ListenerRegister& reg)
    {
        reg.remove(this);
    }
}
