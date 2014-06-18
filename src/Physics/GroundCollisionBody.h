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

#ifndef PHYSICS_GROUND_COLLISION_BODY_H
#define PHYSICS_GROUND_COLLISION_BODY_H

#include <vector>
#include <cmath>

#include "CollisionBody.h"
#include "../Geometry/Vec2D.h"

namespace Physics
{
    typedef std::vector< std::vector<float> > Heightmap;

    class GroundCollisionBody: public CollisionBody
    {
    public:
        static const Type Type;

        GroundCollisionBody():
             CollisionBody(Type)
        {}

        GroundCollisionBody(float chunkSize, float resolution, const Heightmap& heightmap):
             CollisionBody(Type),
             chunkSize_(chunkSize),
             resolution_(resolution),
             heightmap_(heightmap)
        {}

        void setChunkSize(float chunkSize)
        {
            chunkSize_ = chunkSize;
        }

        void setResolution(float resolution)
        {
            resolution_ = resolution;
        }

        void setHeightmap(const Heightmap& heightmap)
        {
            heightmap_ = heightmap;
        }

        /**
        *   @param position : relative position vector (position to check - ground position)
        */
        bool isOnChunk(const Geometry::Vec2Df& position) const
        {
            return position.getX() >= 0 && position.getX() < chunkSize_
            && position.getY() >= 0 && position.getY() < chunkSize_;
        }

        /**
        *   @param position : relative position vector (position to check - ground position)
        *   @return height by bilinear interpolation
        */
        float getHeight(const Geometry::Vec2Df& position) const
        {
            float x = position.getX() / resolution_;
            float y = position.getY() / resolution_;
            float floorX = std::floor(x);
            float floorY = std::floor(y);
            unsigned int i = static_cast<unsigned int>(floorX);//position.getX() / resolution_);
            unsigned int j = static_cast<unsigned int>(floorY);//position.getY() / resolution_);

            return heightmap_[i][j] * (floorX + 1.0f - x) * (floorY + 1.0f - y)
                + heightmap_[i+1][j] * (x - floorX) * (floorY + 1.0f - y)
                + heightmap_[i][j+1] * (floorX + 1.0f - x) * (y - floorY)
                + heightmap_[i+1][j+1] * (x - floorX) * (y - floorY);
        }

    private:
        float chunkSize_;
        float resolution_;
        Heightmap heightmap_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
