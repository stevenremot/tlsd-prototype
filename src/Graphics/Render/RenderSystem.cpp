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
        RenderSystem::RenderSystem(Ecs::World& world, Event::EventQueue& eventQueue) :
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
                    ComponentGroup group = getWorld().getEntityComponents(entity, prototype);

                    const PositionComponent& positionComponent =
                        static_cast<const PositionComponent&>(group.getComponent(PositionComponent::Type));
                    const RotationComponent& rotationComponent =
                        static_cast<const RotationComponent&>(group.getComponent(RotationComponent::Type));
                    const RenderableComponent& renderableComponent =
                        static_cast<const RenderableComponent&>(group.getComponent(RenderableComponent::Type));

                    if (renderableComponent.getMeshFileName() != "")
                    {
                        if (getWorld().hasComponent(entity, AnimationComponent::Type))
                            eventQueue_ << new RenderAnimatedMeshFileEvent(
                                            renderableComponent.getMeshFileName(),
                                            renderableComponent.getTextureFileName(),
                                            positionComponent.getPosition(),
                                            rotationComponent.getRotation(),
                                            entity
                                        );
                        else
                            eventQueue_ << new RenderMeshFileEvent(
                                            renderableComponent.getMeshFileName(),
                                            renderableComponent.getTextureFileName(),
                                            positionComponent.getPosition(),
                                            rotationComponent.getRotation(),
                                            entity
                                        );
                    }
                    else
                        eventQueue_ << new RenderModel3DEvent(
                                        renderableComponent.getModel3d(),
                                        positionComponent.getPosition(),
                                        rotationComponent.getRotation(),
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
