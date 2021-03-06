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

#ifndef WORLD_ENTITY_CREATOR_H
#define WORLD_ENTITY_CREATOR_H

#include <memory>

#include "../Ecs/EntityDescriptor.h"
#include "World.h"
#include "../Ecs/World.h"
#include "BuildingInterface.h"
#include "RoadNetwork.h"
#include "TreeInterface.h"

namespace World
{
    /**
     * Returns the created ground entity for the chunk and insert it in the ecs world
     *
     * TODO : Add "const" to world
     */
    std::shared_ptr<Ecs::EntityDescriptor> createGround(World& world, int i, int j);

    /**
     * Create an entity for the road, and insert it in the ECS world
     */
    std::shared_ptr<Ecs::EntityDescriptor> createRoad(const RoadNetwork& road);


    /**
     * Create an entity for the building, and insert it in the ECS world
     *
     * TODO Add physical component
     */
    std::shared_ptr<Ecs::EntityDescriptor> createBuilding(const BuildingInterface& building);


    /**
     * Create an entity for a tree and insert it in the ECS world
     *
     * TODO Add physical component
     */
    std::shared_ptr<Ecs::EntityDescriptor> createTree(const Geometry::Vec3Df& position, const TreeInterface& tree);

}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
