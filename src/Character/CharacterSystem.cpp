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
#include "HandAction.h"
#include "DieAction.h"
#include "ActionPerformedEvent.h"
#include "CharacterComponent.h"
#include "GroupComponent.h"
#include "EntityCreator.h"
#include "../Input/PlayerComponent.h"
#include "../Physics/MovementComponent.h"
#include "../Physics/EntityRotationChangedEvent.h"
#include "../Graphics/Render/AnimateActionEvent.h"

// TODO remove
#include <iostream>

using Geometry::Vec2Df;
using Geometry::Vec3Df;
using Threading::ConcurrentRessource;
using Threading::ConcurrentReader;
using Threading::ConcurrentWriter;
using Threading::getConcurrentReader;
using Threading::getConcurrentWriter;

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
                ConcurrentWriter<Ecs::World> world = getWorld();
                const ActionPerformedEvent& actionEvent =
                    dynamic_cast<const ActionPerformedEvent&>(*event);

                const Ecs::Entity& entity = actionEvent.getEntity();
                const Character::Action& action = actionEvent.getAction();

                bool isGroup = world->hasComponent(entity, GroupComponent::Type);

                if (!isGroup)
                {
                    Ecs::ComponentGroup::ComponentTypeCollection types;
                    types.insert(CharacterComponent::Type);
                    types.insert(Geometry::RotationComponent::Type);
                    types.insert(Physics::MovementComponent::Type);
                    Ecs::ComponentGroup prototype(types);
                    Ecs::ComponentGroup group =
                        world->getEntityComponents(entity, prototype);

                    bool hasPlayer = world->hasComponent(entity, Input::PlayerComponent::Type);
                    bool stopAttack = false;

                    ConcurrentRessource<Ecs::Component> charComponentRessource =
                        group.getComponent(CharacterComponent::Type);

                    ConcurrentRessource<Ecs::Component> rotComponentRessource =
                        group.getComponent(Geometry::RotationComponent::Type);

                    ConcurrentRessource<Ecs::Component> movComponentRessource =
                        group.getComponent(Physics::MovementComponent::Type);

                    if (action.getType() == MoveAction::Type)
                    {
                        ConcurrentReader<CharacterComponent> charComponent =
                            getConcurrentReader<Ecs::Component, CharacterComponent>(
                                charComponentRessource
                            );

                        ConcurrentWriter<Physics::MovementComponent> movComponent =
                            getConcurrentWriter<Ecs::Component, Physics::MovementComponent>(
                                movComponentRessource
                            );

                        Vec2Df direction2D = dynamic_cast<const MoveAction&>(action).getDirection();
                        movComponent->setVelocity(direction2D * charComponent->getWalkingSpeed());
                        movComponent->setBaseVelocity(direction2D * charComponent->getWalkingSpeed());

                        outsideQueue_ << new Graphics::Render::AnimateActionEvent(entity, MoveAction::Type);
                    }
                    else if (action.getType() == StopAction::Type)
                    {
                        ConcurrentReader<CharacterComponent> charComponent =
                            getConcurrentReader<Ecs::Component, CharacterComponent>(
                                charComponentRessource
                            );

                        ConcurrentWriter<Physics::MovementComponent> movComponent =
                            getConcurrentWriter<Ecs::Component, Physics::MovementComponent>(
                                movComponentRessource
                            );

                        movComponent->setVelocity(Vec2Df(0,0));
                        movComponent->setBaseVelocity(Vec2Df(0,0));


                        outsideQueue_ << new Graphics::Render::AnimateActionEvent(entity, StopAction::Type);
                    }
                    else if (action.getType() == LookAtAction::Type)
                    {
                        ConcurrentWriter<Geometry::RotationComponent> rotComponent =
                            getConcurrentWriter<Ecs::Component, Geometry::RotationComponent>(
                                rotComponentRessource
                            );

                        ConcurrentWriter<Physics::MovementComponent> movComponent =
                            getConcurrentWriter<Ecs::Component, Physics::MovementComponent>(
                                movComponentRessource
                            );
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
                        Vec2Df currentDirection =
                            movComponent->getVelocity().getHorizontalComponent();
                        float currentAngle = currentDirection.getOrientation();
                        currentAngle += orientation - currentOrientation.getZ();
                        Vec2Df newDirection =
                            Geometry::Vec2Df::fromPolar(currentAngle, currentDirection.getLength());
                        movComponent->setVelocity(newDirection);

                        // update base velocity orientation
                        currentDirection =
                            movComponent->getBaseVelocity().getHorizontalComponent();
                        currentAngle = currentDirection.getOrientation();
                        currentAngle += orientation - currentOrientation.getZ();
                        newDirection =
                            Geometry::Vec2Df::fromPolar(currentAngle, currentDirection.getLength());
                        movComponent->setBaseVelocity(newDirection);

                        if (!hasPlayer)
                        {
                            outsideQueue_ << new Physics::EntityRotationChangedEvent(
                                              entity,
                                              rotComponent->getRotation()
                                          );
                        }
                    }
                    else if (action.getType() == StartHandAction::Type)
                    {
                        {
                            ConcurrentWriter<Physics::MovementComponent> movComponent =
                                getConcurrentWriter<Ecs::Component, Physics::MovementComponent>(
                                    movComponentRessource
                                );

                            movComponent->setVelocity(
                                Vec2Df(0, 0)
                            );
                            movComponent->setBaseVelocity(Vec2Df(0, 0));
                        }

                        outsideQueue_ << new Graphics::Render::AnimateActionEvent(entity, StartHandAction::Type);
                        createAttackArea(world, entity);

                        getConcurrentWriter<Ecs::Component, CharacterComponent>(
                            charComponentRessource
                        )->setAttacking(true);
                    }
                    else if (action.getType() == StopHandAction::Type)
                    {
                        stopAttack = true;
                        outsideQueue_ << new Graphics::Render::AnimateActionEvent(entity, StopAction::Type);
                    }

                    if (stopAttack &&
                            getConcurrentReader<Ecs::Component, CharacterComponent>(
                                charComponentRessource
                            )->isAttacking()
                       )
                    {
                        world->removeEntity(
                            getConcurrentReader<Ecs::Component, CharacterComponent>(
                                charComponentRessource
                            )->getAttackArea()
                        );

                        getConcurrentWriter<Ecs::Component, CharacterComponent>(
                            charComponentRessource
                        )->setAttacking(false);
                    }
                }
                else
                {
                    std::list<Ecs::Entity> entitiesToRemove;
                    {
                        ConcurrentReader<GroupComponent> groupComponent =
                            getConcurrentReader<Ecs::Component, GroupComponent>(
                                world->getEntityComponent(entity, GroupComponent::Type)
                            );


                        if(action.getType() == DieAction::Type)
                        {
                            entitiesToRemove.push_back(entity);
                            const GroupComponent::EntityCollection& entities =
                                groupComponent->getEntities();
                            GroupComponent::EntityCollection::const_iterator ent;

                            for (ent = entities.begin(); ent != entities.end(); ++ent)
                            {
                                entitiesToRemove.push_back(*ent);
                            }
                        }
                    }

                    std::list<Ecs::Entity>::iterator ent;
                    for (ent = entitiesToRemove.begin(); ent != entitiesToRemove.end(); ++ent)
                    {
                        world->removeEntity(*ent);
                    }
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
