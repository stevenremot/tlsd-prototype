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

#include <iostream>

namespace World
{
	Ecs::SharedEntity createGround(World& world, int i, int j, Ecs::World& ecsWorld)
	{
		Ecs::SharedEntity groundEntity = ecsWorld.createSharedEntity();

		ecsWorld.addComponent(
            groundEntity.getEntity(),
            new Geometry::PositionComponent(
                Geometry::Vec3Df(
                    i*static_cast<int>(World::ChunkSize),
                    j*static_cast<int>(World::ChunkSize),
                    0
                )
            )
        );

        ecsWorld.addComponent(
            groundEntity.getEntity(),
            new Geometry::RotationComponent(
                Geometry::Vec3Df(0, 0, 0)
            )
        );

        ecsWorld.addComponent(
            groundEntity.getEntity(),
            new Graphics::Render::RenderableComponent(computeGroundModel(world, i, j))
        );

		return groundEntity;
	}

    Ecs::Entity createRoad(const RoadNetwork& road, Ecs::World& ecsWorld)
    {
        Ecs::Entity entity = ecsWorld.createEntity();

        ecsWorld.addComponent(
            entity,
            new Geometry::PositionComponent(Geometry::Vec3Df())
        );

        return entity;
    }

    Ecs::Entity createBuilding(const BuildingInterface& building, Ecs::World& ecsWorld)
    {
        Ecs::Entity entity = ecsWorld.createEntity();

        ecsWorld.addComponent(
            entity,
            new Geometry::PositionComponent(Geometry::Vec3Df())
        );

        return entity;
    }
}