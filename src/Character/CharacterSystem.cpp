#include "CharacterSystem.h"

#include "MoveAction.h"
#include "ActionPerformedEvent.h"
#include "CharacterComponent.h"
#include "../Physics/MovementComponent.h"
#include "../Graphics/Render/AnimateActionEvent.h"

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
            Ecs::World& world = getWorld();

            Event::Event* event = NULL;
            eventHead_ >> event;

            if (event != NULL)
            {
                const ActionPerformedEvent& actionEvent =
                    dynamic_cast<const ActionPerformedEvent&>(*event);

                const Ecs::Entity& entity = actionEvent.getEntity();
                const Character::Action& action = actionEvent.getAction();

                const CharacterComponent& charComponent =
                    dynamic_cast<const CharacterComponent&>(
                        world.getEntityComponent(entity, CharacterComponent::Type)
                    );

                if (action.getType() == MoveAction::Type)
                {
                    Physics::MovementComponent& movementComponent =
                        dynamic_cast<Physics::MovementComponent&>(
                            world.getEntityComponent(entity, Physics::MovementComponent::Type)
                        );

                    Vec2Df direction2D = dynamic_cast<const MoveAction&>(action).getDirection();
                    Vec3Df velocity =
                        Vec3Df(direction2D.getX(), direction2D.getY(), 0) * charComponent.getWalkingSpeed();

                    movementComponent.setVelocity(velocity);

                    outsideQueue_ << new Graphics::Render::AnimateActionEvent(entity, MoveAction::Type);
                }
            }
        }
    }
}
