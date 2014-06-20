#include "RenderSystem.h"

#include "../../Ecs/ComponentCreatedEvent.h"
#include "RenderableComponent.h"
#include "AnimationComponent.h"
#include "../../Geometry/PositionComponent.h"
#include "../../Geometry/RotationComponent.h"
#include "RenderEvents.h"
#include "../../Input/PlayerComponent.h"

using Ecs::ComponentCreatedEvent;
using Ecs::ComponentGroup;
using Geometry::PositionComponent;
using Geometry::RotationComponent;

namespace Graphics
{
    namespace Render
    {
        RenderSystem::RenderSystem(
            Threading::ConcurrentRessource<Ecs::World>& world,
            Event::EventQueue& eventQueue
        ) :
            System(world),
            eventQueue_(eventQueue)
        {
        }

        RenderSystem::~RenderSystem()
        {
            //dtor
        }

        void RenderSystem::call(const Event::Event& event)
        {
            if (event.getType() == ComponentCreatedEvent::Type)
            {
                const ComponentCreatedEvent& componentEvent = static_cast<const ComponentCreatedEvent&>(event);

                if (componentEvent.getComponentType() == RenderableComponent::Type)
                {
                    const Ecs::Entity& entity = componentEvent.getEntity();

                    ComponentGroup::ComponentTypeCollection types;
                    types.insert(RenderableComponent::Type);

                    ComponentGroup prototype(types);
                    ComponentGroup group = getWorld()->getEntityComponents(entity, prototype);

                    bool hasAnimation = getWorld()->hasComponent(entity, AnimationComponent::Type);

                    Threading::ConcurrentReader<PositionComponent> positionComponent =
                        Threading::getConcurrentReader<Ecs::Component, PositionComponent>(group.getComponent(PositionComponent::Type));

                    Threading::ConcurrentReader<RotationComponent> rotationComponent =
                        Threading::getConcurrentReader<Ecs::Component, RotationComponent>(group.getComponent(RotationComponent::Type));

                    Threading::ConcurrentReader<RenderableComponent> renderableComponent =
                        Threading::getConcurrentReader<Ecs::Component, RenderableComponent>(group.getComponent(RenderableComponent::Type));

                    if (renderableComponent->getMeshFileName() != "")
                    {
                        if (hasAnimation)
                            eventQueue_ << new RenderAnimatedMeshFileEvent(
                                            renderableComponent->getMeshFileName(),
                                            renderableComponent->getTextureFileName(),
                                            positionComponent->getPosition(),
                                            rotationComponent->getRotation(),
                                            entity
                                        );
                        else
                            eventQueue_ << new RenderMeshFileEvent(
                                            renderableComponent->getMeshFileName(),
                                            renderableComponent->getTextureFileName(),
                                            positionComponent->getPosition(),
                                            rotationComponent->getRotation(),
                                            entity
                                        );
                    }
                    else
                        eventQueue_ << new RenderModel3DEvent(
                                        renderableComponent->getModel3d(),
                                        positionComponent->getPosition(),
                                        rotationComponent->getRotation(),
                                        entity
                                    );
                }
                else if (componentEvent.getComponentType() == Input::PlayerComponent::Type)
                {
                    const Ecs::Entity& entity = componentEvent.getEntity();

                    eventQueue_ << new RenderCameraEvent(entity);
                }
            }
        }
    }
}
