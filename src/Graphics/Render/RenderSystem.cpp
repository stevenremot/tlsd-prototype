#include "RenderSystem.h"

#include "../../Ecs/ComponentCreatedEvent.h"
#include "RenderableComponent.h"
#include "../../Geometry/PositionComponent.h"
#include "../../Geometry/RotationComponent.h"
#include "Events.h"

using Ecs::ComponentCreatedEvent;
using Ecs::ComponentGroup;
using Geometry::PositionComponent;
using Geometry::RotationComponent;

namespace Graphics
{
    namespace Render
    {
        RenderSystem::RenderSystem(World& world, Event::EventQueue& eventQueue) :
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
            if (event.getType() == ComponentCreatedEvent::TYPE)
            {
                const ComponentCreatedEvent& componentEvent = static_cast<const ComponentCreatedEvent&>(event);

                if (componentEvent.getComponentType() == RenderableComponent::Type)
                {
                    const Ecs::Entity& entity = componentEvent.getEntity();

                    ComponentGroup::ComponentTypeCollection types;
                    types.insert(RenderableComponent::Type);
                    types.insert(Geometry::PositionComponent::Type);

                    ComponentGroup prototype(types);
                    ComponentGroup group = getWorld().getEntityComponents(entity, prototype);

                    const PositionComponent& positionComponent = static_cast<const PositionComponent&>(group.getComponent(PositionComponent::Type));
                    const RotationComponent& rotationComponent = static_cast<const RotationComponent&>(group.getComponent(RotationComponent::Type));
                    const RenderableComponent& renderableComponent = static_cast<const RenderableComponent&>(group.getComponent(RenderableComponent::Type));

                    if (renderableComponent.getMeshFileName() != "")
                        eventQueue_ << new RenderMeshFileEvent(renderableComponent.getMeshFileName(), renderableComponent.getTextureFileName(), positionComponent.getPosition(), rotationComponent.getRotation(), entity);
                    else
                        eventQueue_ << new RenderModel3DEvent(renderableComponent.getModel3d(), positionComponent.getPosition(), rotationComponent.getRotation(), entity);
                }
            }
        }
    }
}
