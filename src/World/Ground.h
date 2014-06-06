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

#ifndef WORLD_GROUND_H
#define WORLD_GROUND_H

#include <exception>

#include "../Graphics/Render/Model3D.h"
#include "World.h"

namespace World
{
    /**
     * This exception is raised when the chunk needs to
     * be generated first
     *
     */
    class NotGeneratedChunkException: public std::exception
    {
    public:
        const char* what() const throw()
        {
            return "Trying to compute the 3D model of a not generated chunk";
        }
    };

    /**
     * This exception is raised when the chunk needs to
     * be preparated first
     *
     */
    class NotPreparatedChunkException: public std::exception
    {
    public:
        const char* what() const throw()
        {
            return "Trying to access a not preparated chunk";
        }
    };

    const float Resolution = 2;
    /**
     * Returns the 3D model of the ground for the chunk
     * at the given position
     *
     */
    Graphics::Render::Model3D computeGroundModel(World& world, int x, int y);
    float computeHeight(World& world, float x, float y);

}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
