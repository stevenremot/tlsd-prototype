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

namespace World
{

	Ecs::Entity createGround(const World& world, int i, int j, Ecs::World& ecsWorld)
	{
		Ecs::Entity groundEntity = ecsWorld.createEntity();

		ecsWorld.addComponent(groundEntity, new Geometry::PositionComponent(Geometry::Vec3Df(i*World::ChunkSize,j*World::ChunkSize, 0)));

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
