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

#ifndef AI_NAVMESH_NAVMESHCONTAINER_H
#define AI_NAVMESH_NAVMESHCONTAINER_H

#include <map>
#include <stdexcept>

#include "NavMesh.h"
#include "Obstacle.h"
#include "../../Geometry/Vec2D.h"

namespace AI
{
    namespace NavMesh
    {
        class NavMeshContainer
        {
        public:
            typedef std::map<std::pair<Geometry::Vec2Df, Geometry::Vec2Df>, NavMesh*> NavMeshesMap;

            NavMeshContainer();

            bool getNavMesh(const Geometry::Vec2Df& position, NavMesh*& pNavMesh)
            {
                for(NavMeshesMap::const_iterator it = navMeshesMap_.begin(); it != navMeshesMap_.end(); ++it)
                {
                    const std::pair<Geometry::Vec2Df, Geometry::Vec2Df>& corners = it->first;
                    Rectangle boundingBox(corners.first, corners.second);
                    if(boundingBox.contains(position))
                    {
                        pNavMesh = (it-> second);
                        return true;
                    }
                }
                return false;
            }

            bool getNavMesh(const Geometry::Vec2Df& lowerLeftPoint, const Geometry::Vec2Df& upperRightPoint, NavMesh*& pNavMesh)
            {
                try
                {
                    pNavMesh = navMeshesMap_.at(std::make_pair(lowerLeftPoint, upperRightPoint));
                    return true;
                }
                catch (const std::out_of_range& e)
                {
                    return false;
                }
            }

            void setNavMesh(const Geometry::Vec2Df& lowerLeftPoint, const Geometry::Vec2Df& upperRightPoint, NavMesh* navMesh)
            {
                navMeshesMap_[std::make_pair(lowerLeftPoint, upperRightPoint)] = navMesh;
            }

        private:
            NavMeshesMap navMeshesMap_;
        };
    }
}
#endif // AI_NAVMESH_NAVMESHCONTAINER_H
