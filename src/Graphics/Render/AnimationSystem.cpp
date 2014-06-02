#include "AnimationSystem.h"

#include "../../Ecs/ComponentCreatedEvent.h"
#include "AnimationComponent.h"
#include "AnimationEvents.h"

using Ecs::ComponentCreatedEvent;
using Ecs::ComponentGroup;

namespace Graphics
{
    namespace Render
    {
        const Event::Event::Type DummyActionEvent::TYPE = "dummy_action";

        AnimationSystem::AnimationSystem(World& world, Event::EventQueue& eventQueue):
            System(world),
            eventQueue_(eventQueue)
        {
        }

        AnimationSystem::~AnimationSystem()
        {
            //dtor
        }

        void AnimationSystem::call(const Event::Event& event)
        {
            if (event.getType() == ComponentCreatedEvent::TYPE)
            {
                const ComponentCreatedEvent& componentEvent = static_cast<const ComponentCreatedEvent&>(event);

                if (componentEvent.getComponentType() == AnimationComponent::Type)
                {
                    const Ecs::Entity& entity = componentEvent.getEntity();

                    ComponentGroup::ComponentTypeCollection types;
                    types.insert(AnimationComponent::Type);

                    ComponentGroup prototype(types);
                    ComponentGroup group = getWorld().getEntityComponents(entity, prototype);

                    const AnimationComponent& animComponent = static_cast<const AnimationComponent&>(group.getComponent(AnimationComponent::Type));

                    eventQueue_ << new SetupAnimationEvent(animComponent.getAnimationMap(), entity);
                }
            }
            else if (event.getType() == DummyActionEvent::TYPE)
            {
                const DummyActionEvent& actionEvent = static_cast<const DummyActionEvent&>(event);
                const Ecs::Entity& entity = actionEvent.getEntity();

                ComponentGroup::ComponentTypeCollection types;
                types.insert(AnimationComponent::Type);

                ComponentGroup prototype(types);
                ComponentGroup group = getWorld().getEntityComponents(entity, prototype);

                AnimationComponent& animComponent = static_cast<AnimationComponent&>(group.getComponent(AnimationComponent::Type));

                eventQueue_ << new AnimateEvent(animComponent.getAnimationByAction(actionEvent.getAction()), entity);
            }
        }
    }
}
