#include "AnimationSystem.h"

#include "../../Ecs/ComponentCreatedEvent.h"
#include "AnimationComponent.h"
#include "AnimationEvents.h"
#include "AnimateActionEvent.h"

#include <iostream>

using Ecs::ComponentCreatedEvent;
using Ecs::ComponentGroup;
using Ecs::World;

namespace Graphics
{
    namespace Render
    {
        AnimationSystem::AnimationSystem(
            Threading::ConcurrentRessource<World>& world,
            Event::EventQueue& outsideQueue
        ):
            System(world),
            outsideQueue_(outsideQueue)
        {
            Threading::createChannel(eventQueue_, eventHead_);
        }

        AnimationSystem::~AnimationSystem()
        {
            //dtor
        }

        void AnimationSystem::call(const Event::Event& event)
        {
            if (event.getType() == ComponentCreatedEvent::Type)
            {
                eventQueue_ << new ComponentCreatedEvent(static_cast<const ComponentCreatedEvent&>(event));
            }
            else if (event.getType() == AnimateActionEvent::Type)
            {
                eventQueue_ << new AnimateActionEvent(static_cast<const AnimateActionEvent&>(event));
            }
        }

        void AnimationSystem::run()
        {
            while (!eventHead_.isEmpty())
            {
                Event::Event* event = NULL;
                eventHead_ >> event;

                if (event != NULL)
                {
                    if (event->getType() == ComponentCreatedEvent::Type)
                    {
                        const ComponentCreatedEvent& componentEvent = static_cast<const ComponentCreatedEvent&>(*event);
                        if (componentEvent.getComponentType() == AnimationComponent::Type)
                        {
                            const Ecs::Entity& entity = componentEvent.getEntity();

                            ComponentGroup::ComponentTypeCollection types;
                            types.insert(AnimationComponent::Type);

                            ComponentGroup prototype(types);
                            ComponentGroup group = getWorld()->getEntityComponents(entity, prototype);

                            Threading::ConcurrentReader<AnimationComponent> animComponent =
                                Threading::getConcurrentReader<Ecs::Component, AnimationComponent>(
                                    group.getComponent(AnimationComponent::Type)
                                );

                            outsideQueue_ << new SetupAnimationEvent(animComponent->getAnimationMap(), entity);
                        }
                    }
                    else if (event->getType() == AnimateActionEvent::Type)
                    {
                        const AnimateActionEvent& actionEvent = static_cast<const AnimateActionEvent&>(*event);
                        const Ecs::Entity& entity = actionEvent.getEntity();

                        ComponentGroup::ComponentTypeCollection types;
                        types.insert(AnimationComponent::Type);

                        ComponentGroup prototype(types);
                        ComponentGroup group = getWorld()->getEntityComponents(entity, prototype);
                        Threading::ConcurrentWriter<AnimationComponent> animComponent =
                            Threading::getConcurrentWriter<Ecs::Component, AnimationComponent>(
                                group.getComponent(AnimationComponent::Type)
                            );

                        outsideQueue_ << new AnimateEvent(animComponent->getAnimationByAction(actionEvent.getAction()), entity);
                    }
                }
            }

            // Get all the entities with animation component
            Ecs::ComponentGroup::ComponentTypeCollection types;
            types.insert(AnimationComponent::Type);

            Ecs::ComponentGroup prototype(types);
            Ecs::World::ComponentGroupCollection groups = getWorld()->getComponents(prototype);

            // Send UpdateAnimationEvents
            Ecs::World::ComponentGroupCollection::iterator group;
            for (group = groups.begin(); group != groups.end(); ++group)
            {
                outsideQueue_ << new UpdateAnimationEvent(group->getEntity());
            }
        }

        void AnimationSystem::registerListeners(Event::ListenerRegister& reg)
        {
            reg.put(Ecs::ComponentCreatedEvent::Type, this);
            reg.put(AnimateActionEvent::Type, this);
        }
    }
}
