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

#include "EntityCreator.h"
#include "../Geometry/PositionComponent.h"
#include "../Geometry/RotationComponent.h"
#include "../Graphics/Render/RenderableComponent.h"
#include "Ground.h"
#include "../Physics/GroundCollisionBody.h"
#include "../Physics/Model3DCollisionBody.h"
#include "../Physics/CollisionComponent.h"

namespace World
{
    Core::SharedPtr<Ecs::EntityDescriptor> createGround(World& world, int i, int j)
	{
        Core::SharedPtr<Ecs::EntityDescriptor> groundEntity(new Ecs::EntityDescriptor);

		groundEntity->addComponent(
            new Geometry::PositionComponent(
                Geometry::Vec3Df(
                    i*static_cast<int>(World::ChunkSize),
                    j*static_cast<int>(World::ChunkSize),
                    0
                )
            )
        );

        groundEntity->addComponent(
            new Geometry::RotationComponent(
                Geometry::Vec3Df(0, 0, 0)
            )
        );

        Graphics::Render::Model3D model;
        Physics::GroundCollisionBody* collBody = new Physics::GroundCollisionBody();
        computeGroundModel(world, i, j, model, *collBody);

        groundEntity->addComponent(
            new Graphics::Render::RenderableComponent(model)
        );

        groundEntity->addComponent(
            new Physics::CollisionComponent(collBody)
        );

        return groundEntity;
    }

    Core::SharedPtr<Ecs::EntityDescriptor> createRoad(const RoadNetwork& road)
    {
        Core::SharedPtr<Ecs::EntityDescriptor> entity(new Ecs::EntityDescriptor);

        entity->addComponent(
            new Geometry::PositionComponent(Geometry::Vec3Df(0.0, 0.0, 0.1))
        );

        entity->addComponent(
            new Geometry::RotationComponent(Geometry::Vec3Df())
        );

        entity->addComponent(
            new Graphics::Render::RenderableComponent(road.getModel())
        );

        return entity;
    }

    Core::SharedPtr<Ecs::EntityDescriptor> createBuilding(const BuildingInterface& building)
    {
        Core::SharedPtr<Ecs::EntityDescriptor> entity(new Ecs::EntityDescriptor);

        Geometry::Vec3Df pos = Geometry::Vec3Df(0.0, 0.0, 0.1);

        entity->addComponent(
            new Geometry::PositionComponent(pos)
        );

        entity->addComponent(
            new Geometry::RotationComponent(Geometry::Vec3Df())
        );

        entity->addComponent(
            new Graphics::Render::RenderableComponent(building.getModel())
        );
        entity->addComponent(
            new Physics::CollisionComponent(new Physics::Model3DCollisionBody(building.getModel(), pos))
        );

        return entity;
    }

    Core::SharedPtr<Ecs::EntityDescriptor> createTree(const Geometry::Vec3Df& position, const TreeInterface& tree)
    {
        Core::SharedPtr<Ecs::EntityDescriptor> entity(new Ecs::EntityDescriptor);

        entity->addComponent(
            new Geometry::PositionComponent(position)
        );

        entity->addComponent(
            new Geometry::RotationComponent(Geometry::Vec3Df())
        );

        entity->addComponent(
            new Graphics::Render::RenderableComponent(tree.getModel())
        );
        entity->addComponent(
            new Physics::CollisionComponent(new Physics::Model3DCollisionBody(tree.getModel(), position))
        );

        return entity;
    }
}
